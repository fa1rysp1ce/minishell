/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:17:35 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/20 18:39:17 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    clean_shell(t_shell *shell)
{
    if (shell->envc)
        free_2d_charr(shell->envc);
    //destroy tokens
    clean_tokens(shell->head_token);
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
    int     i;
    
    if (exec->heredocs)
    {
        i = 0;
        while (i < exec->hdocs)
        {
            if (exec->heredocs[i].read_end_open == 1)
            {
                close(exec->heredocs[i].doc_pipe[0]);
                exec->heredocs[i].read_end_open = 0;
            }
            i++;
        }
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

