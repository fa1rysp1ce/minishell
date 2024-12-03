/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:19:05 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/03 17:39:44 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     is_builtin(char *str)
{   
    if (!ft_strcmp(str, "echo"))
        return (1);
    if (!ft_strcmp(str, "export"))
        return (1);
    if (!ft_strcmp(str, "pwd"))
        return (1);
    if (!ft_strcmp(str, "env"))
        return (1);
    if (!ft_strcmp(str, "unset"))
        return (1);
    if (!ft_strcmp(str, "exit"))
        return (1);
    if (!ft_strcmp(str, "cd"))
        return (1);
    return (0);
}

int     execute_builtin(t_shell *shell)
{   
    char    *str;
    t_token *token;

    token = shell->token;
    str = token->args[0];
    if (!ft_strcmp(str, "echo"))
        return (echo(token));
    if (!ft_strcmp(str, "export")) //may have malloc failure
       return (export(shell, token)); //try this in a child process - shouldnt save changes
    if (!ft_strcmp(str, "pwd"))
        return (pwd());
    if (!ft_strcmp(str, "env"))
        return (env(shell));
    if (!ft_strcmp(str, "unset")) //may have malloc failure
        return (unset(shell, token));
    if (!ft_strcmp(str, "cd"))
        cd(shell);
    if (!ft_strcmp(str, "exit"))
        return (exit_cmd(shell));
    return (EXIT_FAILURE);
}

//copy src string into dest variable in the envoirment vars
int		change_env(t_shell *shell, char *src, char *dest)
{
    char	*new;
    int     i;

    if (src == NULL || expand_arg(shell, dest) == NULL)
        return (EXIT_FAILURE);
    dest = ft_strjoin(dest, "=");
    new = ft_strjoin(dest, src);
    if (dest == NULL || new == NULL)
    {
        free(src);
        return (exit_malloc_err(shell));
    }
    i = 0;
    while (shell->envc[i] != NULL)
    {
        if (ft_strncmp(shell->envc[i], dest, ft_strlen(dest)) == 0)
            break;
        i++;
    }
    free(dest);
    free(shell->envc[i]);
    shell->envc[i] = new;
	return (EXIT_SUCCESS);
}
