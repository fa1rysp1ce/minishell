/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:03:54 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/11 20:02:52 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    init_execute(t_shell *shell);
static int    count_pipes(t_token **token);
static void    single_builtin(t_shell *shell);

//navigates the list of tokens into the correct functions
void    execution_junction(t_shell *shell, t_token **head_token)
{   
    shell->head_token = head_token;
    shell->token = (*shell->head_token);
    init_execute(shell);
    if (process_heredocs(shell) == EXIT_SUCCESS) //connect appropriate exit status
    {
        // if (shell->token->args[0] != NULL)
        {
            if (shell->execute->cmds == 1 && is_builtin(shell->token->args[0]))
                single_builtin(shell);
            else
                pipeline(shell);
        }
    }
    clean_heredocs(shell->execute);
    free(shell->execute);
    shell->execute = NULL;
}

//initialize the execution structure
static void    init_execute(t_shell *shell)
{   
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
}

static int    count_pipes(t_token **token)
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

static void    single_builtin(t_shell *shell)
{
    int         status;

    if (redirection(shell, &status) != EXIT_FAILURE)
        status = execute_builtin(shell);
    set_exit_status(status);
    restore_fds(shell);
}
