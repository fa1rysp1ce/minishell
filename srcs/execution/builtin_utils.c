/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:19:05 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/22 18:00:11 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exit_cmd(t_shell *shell)
{
    clean_exec(shell);
    clean_tokens(shell);
    clean_shell(shell);
    exit(EXIT_SUCCESS);
}

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
    char *str;
    t_token *token;

    token = shell->token;
    str = token->args[0];
    if (!ft_strcmp(str, "echo"))
        return (echo(token));
    if (!ft_strcmp(str, "export")) //may have malloc failure
       return (export(shell, token)); //try this in a child process - shouldnt save changes
    if (!ft_strcmp(str, "pwd"))
        return (pwd(shell));
    if (!ft_strcmp(str, "env"))
        return (env(shell));
    if (!ft_strcmp(str, "unset")) //may have malloc failure
        return (unset(shell, token));
    if (!ft_strcmp(str, "cd"))
        cd(shell);
    if (!ft_strcmp(str, "exit"))
        exit_cmd(shell);
    return (EXIT_FAILURE);
}
