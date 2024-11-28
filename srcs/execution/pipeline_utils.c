/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:58:32 by inbar             #+#    #+#             */
/*   Updated: 2024/11/28 17:13:55 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//will push shell->token to the next token that is a command. NULL if there is no
void    next_cmd_token(t_shell *shell)
{
    while (shell->token->next != NULL)
    {
        shell->token = shell->token->next;
        if (shell->token->type == CMD)
            return ;
    }
}

void    close_pipes(int pipe_fd[2][2], int pipe)
{
    close(pipe_fd[pipe][0]);
    close(pipe_fd[pipe][1]);
}

void    swap_pipes(int *last_pipe, int *new_pipe)
{
    int     tmp;

    tmp = *last_pipe;
    *last_pipe = *new_pipe;
    *new_pipe = tmp;
}

//TODO add signal part
void    update_exit_status(t_shell *shell, int status)
{
        shell->last_exit_status = status;
        if (WIFEXITED(status))
            shell->last_exit_status = WEXITSTATUS(status);
        
}

void    child_exec_fail(t_shell *shell)
{
    restore_fds(shell);
    clean_exec(shell);
    clean_tokens(shell);
    clean_shell(shell);
}
