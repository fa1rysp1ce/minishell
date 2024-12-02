/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:17:35 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/02 13:06:12 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    clean_shell(t_shell *shell)
{
    if (shell->envc)
        free_2d_charr(shell->envc);
    //destroy tokens
    // clean_tokens(shell->head_token);
}

void    clean_tokens(t_shell *shell)
{
    free_list(shell->head_token);
    shell->head_token = NULL;
    shell->token = NULL;
}

void    clean_exec(t_shell *shell)
{
    if (shell->execute->org_fds)
    {
        // restore_fds(shell);
        free(shell->execute->org_fds);
    }
    shell->execute->org_fds = NULL;
    if (shell->execute->pid)
        free(shell->execute->pid);
    shell->execute->pid = NULL;
    clean_heredocs(shell->execute);
    if (shell->execute) //is there anything still mallocd inside?
        free(shell->execute);
    shell->execute = NULL;
}

void    clean_heredocs(t_execute *exec)
{
    // int     i;
    
    if (exec->heredocs)
    {
        //for some reason it closes the last heredoc again - no error reported
        // i = 0;
        // while (i < exec->hdocs)
        // {
        //     if (exec->heredocs[i].read_end_open == 1)
        //     {
        //         printf("open heredoc[%d] : closing it while cleaning\n", i);
        //         close(exec->heredocs[i].doc_pipe[0]);
        //         // free(exec->heredocs[i].read_end_open);
        //         //*exec->heredocs[i].read_end_open) = 0;
        //     }
        //     i++;
        // }
    }
    free(exec->heredocs);
    exec->heredocs = NULL;
}

void    free_2d_charr(char **arr)
{
    int i;

    i = 0;
    while (arr[i] != NULL)
        free(arr[i++]);
    free(arr);
}

