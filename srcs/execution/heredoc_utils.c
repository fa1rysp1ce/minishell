/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:51:25 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/12 17:01:05 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_heredocs(t_shell *shell)
{
	int		count;
	t_token	*tmp;

	tmp = shell->token;
	count = 0;
	while (tmp != NULL)
	{
		if (tmp->type == HDOC)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

/* returns the next (or first) heredoc token in the list.
	if no heredocs returns null */
void	get_next_heredoc(t_token *token, t_token **doc_token)
{
	t_token	*tmp;

	tmp = *doc_token;
	if (tmp == NULL)
		tmp = token;
	else
		tmp = tmp->next;
	while (tmp != NULL && tmp->type != HDOC)
		tmp = tmp->next;
	*doc_token = tmp;
}

/* during pipeline, closes all heredocs pipes of the associated cmd,
	if there are any */
void	close_used_heredocs(t_shell *shell)
{
	t_token	*current_token;
	int		i;
	int		hdocs;

	hdocs = shell->execute->hdocs;
	if (hdocs == 0)
		return ;
	i = 0;
	while (i < hdocs && shell->execute->heredocs[i].read_end_open == 0)
		i++;
	current_token = shell->token->next;
	while (i < hdocs && current_token && (current_token->type != PIPE))
	{
		if (current_token && current_token->type == HDOC)
		{
			close(shell->execute->heredocs[i].doc_pipe[READ_END]);
			shell->execute->heredocs[i].read_end_open = 0;
			i++;
		}
		current_token = current_token->next;
	}
}

void	heredoc_eof_warning(char *delimiter)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}
