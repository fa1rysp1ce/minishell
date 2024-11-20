/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:50:04 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/20 14:20:56 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void    get_next_heredoc(t_token *token, t_token **doc_token)
{
    t_token     *tmp;

    tmp = *doc_token;
    if (tmp == NULL)
    {
        tmp = token;
        while (tmp != NULL && tmp->type != HDOC)
            tmp = tmp->next;
    }
    else
    {
        tmp = tmp->next;
        
        while (tmp != NULL && tmp->type != HDOC)
            tmp = tmp->next;
    }
    *doc_token = tmp;
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

char    *read_heredoc(t_token *doc_token)
{
    char    *delimiter;
    char *line;
    
    rl_initialize();
    delimiter = doc_token->args[0];
    // (void)delimiter;
    
    while ((line = readline("> ")) != NULL)
    {
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break ;
        }
        add_history(line);
        return (line);
        // free(line);
    }
    return (ft_strdup("heredoc text heyoyre\nherehre\ntexttext\n"));
}

int    process_heredocs(t_shell *shell)
{
    t_heredoc *heredocs;
    t_token   *doc_token;
    int     i;

    heredocs = NULL;
    doc_token = NULL;
    i = 0;
    if (!shell->execute->hdocs)
        return (EXIT_SUCCESS);
    heredocs = malloc(sizeof(t_heredoc) * shell->execute->hdocs);
    if (heredocs == NULL)
        exit_malloc_err(shell);
    while (i < shell->execute->hdocs)
    {
        get_next_heredoc(shell->token, &doc_token);
        if (pipe(heredocs[i].doc_pipe) == -1)
            abort_exec("Error: heredoc pipe\n", shell);
        //all these stuff may happen in a child proc
        heredocs[i].content = read_heredoc(doc_token); //strdup content
        heredocs[i].length = ft_strlen(heredocs[i].content);
        // printf("heredoc process: %s\n", heredocs[i].content);
        write(heredocs[i].doc_pipe[1], heredocs[i].content, heredocs[i].length);
        close(heredocs[i].doc_pipe[1]);
        free(heredocs[i].content);
        heredocs[i].content = NULL;
        heredocs[i].read_end_open = 1;
        i++;
    }
    shell->execute->heredocs = heredocs;
    return (EXIT_SUCCESS);
}
