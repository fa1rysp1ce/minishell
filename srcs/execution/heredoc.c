/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:50:04 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/27 23:13:05 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cat <<d1 <<d2 | cat <<d3
//close all heredocs of associated cmd, if there are any
void    close_used_heredocs(t_shell *shell)
{
    t_token     *current_token;
    int         i;

    if (shell->execute->hdocs == 0)
        return ;
    i = 0;
    while (shell->execute->heredocs[i].read_end_open == 0)
        i++;
    current_token = shell->token->next; //current cmd next token
    while (i < shell->execute->hdocs && current_token && (current_token->type != PIPE))
    {
        if (current_token && current_token->type == HDOC)
        {
            printf("open heredoc[%d] : closing in parent during pipe\n", i);
            close(shell->execute->heredocs[i].doc_pipe[0]);
            shell->execute->heredocs[i].read_end_open = 0;
            i++;
        }
        current_token = current_token->next;
    }
}

//if *doc_token is null - returns the first heredoc node in the token list
//else the next heredoc in list after doc_token. if no more heredocs returns null.
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
    if (tmp)
        printf("next doc: %s\n", tmp->args[0]);
}

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

int    *read_heredoc(t_token *doc_token, t_heredoc heredoc)
{
    char    *delimiter;
    char    *line;
    int     line_len;
    
    rl_initialize();
    delimiter = doc_token->args[0];
    
    while ((line = readline("> ")) != NULL)
    {
        if (!line || ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break ;
        }
        line_len = ft_strlen(line);
        write(heredoc.doc_pipe[1], line, line_len);
        write(heredoc.doc_pipe[1], "\n", 1);
        add_history(line);
        free(line);
    }
    close(heredoc.doc_pipe[1]);
    return (EXIT_SUCCESS);
}

int    process_heredocs(t_shell *shell)
{
    t_token   *doc_token;
    int     i;

    doc_token = NULL;
    if (!shell->execute->hdocs)
        return (EXIT_SUCCESS);
    shell->execute->heredocs = malloc(sizeof(t_heredoc) * shell->execute->hdocs);
    if (shell->execute->heredocs == NULL)
        exit_malloc_err(shell);
    i = 0;
    while (i < shell->execute->hdocs)
    {
        get_next_heredoc(shell->token, &doc_token);
        if (pipe(shell->execute->heredocs[i].doc_pipe) == -1)
            abort_exec("Error: heredoc pipe\n", shell);
        
        
        //all these stuff may happen in a child proc
        printf("reading heredocs[%d]\n", i);
        read_heredoc(doc_token, shell->execute->heredocs[i]);
        shell->execute->heredocs[i].read_end_open = 1;
        
        i++;
    }
    return (EXIT_SUCCESS);
}
