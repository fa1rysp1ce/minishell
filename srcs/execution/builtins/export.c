/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:30:23 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/09 17:03:01 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    add_new_env(t_shell *shell, int indx);
static void    add_existing_env(t_shell *shell, char *var_name, int indx);

int    export(t_shell *shell, t_token *token)
{

    char    *equal;
    char    *var_name;
    int     i;
    
    if (token->args[1] == NULL)
        return (env(shell));
    i = 1;
    while (token->args[i] != NULL)
    {
        equal = ft_strchr(token->args[i], '=');
        if (equal != NULL) 
        {
            var_name = ft_substr(token->args[i], 0, (equal - token->args[i]));
            if (expand_arg(shell, var_name) == NULL)
                add_new_env(shell, i);
            else
                add_existing_env(shell, var_name, i);
            free(var_name);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

static void    add_new_env(t_shell *shell, int indx)
{
    int     i;
    
    i = 0;
    while (shell->envc[i] != NULL)
        i++;
    shell->envc = (char **) realloc(shell->envc, ((i + 2) * sizeof(char *)));
    if (shell->envc == NULL)
        exit_malloc_err(shell);
    shell->envc[i] = ft_strdup(shell->token->args[indx]);
    if (shell->envc[i] == NULL)
        exit_malloc_err(shell);
    shell->envc[i + 1] = NULL;
}

static void    add_existing_env(t_shell *shell, char *var_name, int indx)
{
    int     i;
    int     len;
    char    *content;

    i = 0;
    while (shell->token->args[indx][i] != '\0' && shell->token->args[indx][i] != '=')
        i++;
    len = ft_strlen(shell->token->args[indx]) - (i + 1);
    content = ft_substr(shell->token->args[indx], i+1, len);    
    change_env(shell, content, var_name);
}
