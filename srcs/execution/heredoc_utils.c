/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:51:25 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/06 12:09:49 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    count_heredocs(t_shell *shell)
{
    int     count;
    t_token *tmp;

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

// returns the next (or first) heredoc token in the list. if no heredocs returns null
void    get_next_heredoc(t_token *token, t_token **doc_token)
{
    t_token     *tmp;

    tmp = *doc_token;
    if (tmp == NULL)
        tmp = token;
    else
        tmp = tmp->next;
    while (tmp != NULL && tmp->type != HDOC)
        tmp = tmp->next;
    *doc_token = tmp;
}

// cat <<d1 <<d2 | cat <<d3
//during pipeline, closes all heredocs pipes of the associated cmd, if there are any
void    close_used_heredocs(t_shell *shell)
{
    t_token     *current_token;
    int         i;

    if (shell->execute->hdocs == 0)
        return ;
    i = 0;
    while (shell->execute->heredocs[i].read_end_open == 0)
        i++;
    current_token = shell->token->next;
    while (i < shell->execute->hdocs && current_token && (current_token->type != PIPE))
    {
        if (current_token && current_token->type == HDOC)
        {
            // printf("open heredoc[%d] : closing in parent during pipe\n", i);
            close(shell->execute->heredocs[i].doc_pipe[READ_END]);
            shell->execute->heredocs[i].read_end_open = 0;
            i++;
        }
        current_token = current_token->next;
    }
}