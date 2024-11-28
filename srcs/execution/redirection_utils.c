/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:18:54 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/28 16:16:59 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    save_fds(t_shell *shell)
{
    int *original_fds;

    original_fds = (int *) malloc(sizeof(int) * 2);
    if (original_fds == NULL)
        return (exit_malloc_err(shell));
    original_fds[0] = dup(STDIN_FILENO);
    original_fds[1] = dup(STDOUT_FILENO);
    shell->execute->org_fds = original_fds;
    return (EXIT_SUCCESS);
}

void    restore_fds(t_shell *shell)
{
    int *original_fds;
    
    if (shell->execute->org_fds == NULL)
        return ;
    original_fds = shell->execute->org_fds;
    dup2(original_fds[0], STDIN_FILENO);
    dup2(original_fds[1], STDOUT_FILENO);
    close(original_fds[0]);
    close(original_fds[1]);
    free(original_fds);
    shell->execute->org_fds = NULL;
    // printf("fds have restored\n");
}

void    get_next_redirection(t_token **red_token)
{
    t_token *next_red;
    
    next_red = *red_token;
    next_red = next_red->next;
    if (next_red == NULL || next_red->type == PIPE || next_red->type == CMD)
        *red_token = NULL;
    else
        *red_token = next_red; 
}
