/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:03:54 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/03 19:39:08 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    count_pipes(t_token **token)
{
    t_token *tmp;
    int count;

    count = 0;
    tmp = *token;
    while (tmp != NULL)
    {
        if (tmp->type == PIPE)
            count++;
        tmp = tmp->next;
    }
    return (count);
}

// t_execute *exec is mallocd here
void    execution_junction(t_shell *shell, t_token **head_token)
{   
    shell->head_token = head_token;
    
    shell->token = (*shell->head_token); //assuming the first one is always a CMD!
    
    shell->execute = malloc(sizeof(t_execute));
    if (shell->execute == NULL)
        exit_malloc_err(shell);
    shell->execute->org_fds = NULL;
    shell->execute->heredocs = NULL;
    shell->execute->pid = NULL;
    shell->execute->pipes = count_pipes(shell->head_token);
    // printf("pipes: %d\n", shell->execute->pipes);
    shell->execute->cmds = shell->execute->pipes + 1;
    // printf("cmds: %d\n", shell->execute->cmds);
    shell->execute->hdocs = count_heredocs(shell);
    // printf("hdocs: %d\n", shell->execute->hdocs);
    process_heredocs(shell);
    // printf("##STDOUT:##\n\n");
    if (shell->token->args[0] != NULL)
    {
        if (shell->execute->cmds == 1 && is_builtin(shell->token->args[0]))
            single_builtin(shell);
        else
            pipeline(shell);
    }
    clean_heredocs(shell->execute);
    free(shell->execute);
    shell->execute = NULL;
}

void    single_builtin(t_shell *shell)
{
    int         status;

    if (redirection(shell) == EXIT_FAILURE)
    {
        //update correct status
        return ;
    }
    status = execute_builtin(shell);
    shell->last_exit_status = status;
    restore_fds(shell);
}
