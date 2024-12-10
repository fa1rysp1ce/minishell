/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:37:54 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/10 16:14:32 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    redirect_output(t_token *red_token)
{
    int fd;

    if (red_token->type == OUT_APP)
        fd = open(red_token->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(red_token->args[0], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd < 0)
    {
        error_msg(red_token->args[0], strerror(EACCES));
        return (EXIT_FAILURE);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (EXIT_SUCCESS);
}

int    redirect_input(t_token *red_token)
{
    int fd;

    fd = open(red_token->args[0], O_RDONLY);
    if (fd < 0)
    {
        error_msg(red_token->args[0], strerror(ENOENT));
        return (EXIT_FAILURE);
    }
	if (access(red_token->args[0], R_OK) == -1)
    {
		error_msg(red_token->args[0], strerror(EACCES));
        return (EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (EXIT_SUCCESS);
    
}
/* searches for the next unused heredoc uses and closes it.
    the indication of being closed will only apply for the current process */
int    redirect_heredoc(t_shell *shell)
{
    int        i;

    i = 0;
    while (shell->execute->heredocs[i].read_end_open == 0)
        i++;
    dup2(shell->execute->heredocs[i].doc_pipe[0], STDIN_FILENO);
    close(shell->execute->heredocs[i].doc_pipe[0]);
    shell->execute->heredocs[i].read_end_open = 0;
    return (EXIT_SUCCESS);
}


int    redirection(t_shell *shell, int *status)
{   
    t_token *red_token;
    int error;

    red_token = shell->token;
    error = 0;
    get_next_redirection(&red_token);
    if (red_token != NULL)
        save_fds(shell);
    //if error occured in any - should not check the next
    while (red_token != NULL && error != EXIT_FAILURE)
    {
        if (red_token->type == IN)
            error = redirect_input(red_token);
        else if (red_token->type == HDOC)
            error = redirect_heredoc(shell);
        else if ((red_token->type == OUT || red_token->type == OUT_APP))
            error = redirect_output(red_token);
        get_next_redirection(&red_token);
    }
    if (error == EXIT_FAILURE)
    {
        *status = EXIT_FAILURE;
        restore_fds(shell);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

