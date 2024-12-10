/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:30:23 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/10 15:57:55 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void     export_var(t_shell *shell, int indx, int *status);
static int      valid_identifier(char *str);
static void     add_new_env(t_shell *shell, int indx);
static void     add_existing_env(t_shell *shell, char *var_name, int indx);

int    export(t_shell *shell, t_token *token)
{
    int     i;
    int     status;
    
    status = EXIT_SUCCESS;
    if (token->args[1] == NULL)
        return (env(shell));
    i = 1;
    while (token->args[i] != NULL)
    {
        export_var(shell, i, &status);
        i++;
    }
    return (status);
}

static void     export_var(t_shell *shell, int indx, int *status)
{
    char    *equal;
    char    *var_name;
    t_token *token;
    
    token = shell->token;
    equal = ft_strchr(token->args[indx], '=');
    var_name = ft_substr(token->args[indx], 0, (equal - token->args[indx]));
    // printf("varname: %s\n", var_name);
    if (var_name[0] != '\0' && valid_identifier(var_name))
    {
        if (expand_arg(shell, var_name) == NULL)
            add_new_env(shell, indx);
        else
            add_existing_env(shell, var_name, indx);
    }
    else
    {
        *status = EXIT_FAILURE;
        error_msg(token->args[indx], "not a valid identifier");
    }
    free(var_name);
}

//returns 1 if str follows the rules of naming variables in bash
static int  valid_identifier(char *str)
{
    int     i;

    i = 0;
    if (ft_isalpha(str[i]) || str[i] == '_')
        while (str[++i] != '\0')
        {
            if (!(str[i] == '_' || ft_isalpha(str[i]) || ft_isdigit(str[i])))
                return (0);
        }
    else
        return (0);
    return (1);
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
