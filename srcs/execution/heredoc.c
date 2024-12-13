/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:50:04 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/13 12:36:34 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*read_heredoc(t_heredoc heredoc, char *delimiter);
static void	create_pipes_hdocs(t_shell *shell);
static void	child_process_hdocs(t_shell *shell);
static void	close_parent_pipes(t_shell *shell);

/* reads all heredocs in one child process.
	returns 1 if an heredoc was terminted with ctrl+c. 0 otherwise */
int	process_heredocs(t_shell *shell)
{
	pid_t	pid;
	int		hdoc_status;

	if (!shell->execute->hdocs)
		return (EXIT_SUCCESS);
	shell->execute->heredocs = malloc(sizeof(t_heredoc)
			* shell->execute->hdocs);
	if (shell->execute->heredocs == NULL)
		exit_malloc_err(shell);
	create_pipes_hdocs(shell);
	pid = fork();
	if (pid < 0)
		abort_exec("Error: heredoc fork\n", shell);
	if (pid == 0)
		child_process_hdocs(shell);
	waitpid(pid, &hdoc_status, 0);
	signal_noninteractive();
	close_parent_pipes(shell);
	if (WEXITSTATUS(hdoc_status) == EXIT_FAILURE)
		set_exit_status(SIG_TERM);
	return (WEXITSTATUS(hdoc_status));
}

/* reading heredocs
	and storing their content in corresponding pipes for later use */
static void	*read_heredoc(t_heredoc heredoc, char *delimiter)
{
	char	*line;
	int		line_len;

	rl_initialize();
	close(heredoc.doc_pipe[READ_END]);
	signal_heredoc();
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
		{
			if (line == NULL)
				heredoc_eof_warning(delimiter);
			free(line);
			break ;
		}
		line_len = ft_strlen(line);
		write(heredoc.doc_pipe[WRITE_END], line, line_len);
		write(heredoc.doc_pipe[WRITE_END], "\n", 1);
		add_history(line);
		free(line);
	}
	close(heredoc.doc_pipe[WRITE_END]);
	return (EXIT_SUCCESS);
}

static void	create_pipes_hdocs(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->execute->hdocs)
	{
		if (pipe(shell->execute->heredocs[i].doc_pipe) == -1)
			abort_exec("Error: heredoc pipe\n", shell);
		i++;
	}
}

static void	child_process_hdocs(t_shell *shell)
{
	int		i;
	t_token	*doc_token;

	doc_token = NULL;
	i = 0;
	while (i < shell->execute->hdocs)
	{
		get_next_heredoc(shell->token, &doc_token);
		read_heredoc(shell->execute->heredocs[i], doc_token->args[0]);
		i++;
	}
	clean_heredocs(shell->execute);
	clean_exec(shell);
	clean_tokens(shell);
	clean_shell(shell);
	exit(EXIT_SUCCESS);
}

// close all write-end pipes in parent and flag read-end as open
static void	close_parent_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->execute->hdocs)
	{
		close(shell->execute->heredocs[i].doc_pipe[1]);
		shell->execute->heredocs[i].read_end_open = 1;
		i++;
	}
}
