/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:04:11 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/20 18:39:12 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//{"echo", "-n" / "", "txt...", "txt...", "null"}
int     echo(t_token *token)
{
    int i;
    int new_line;

    i = 1;
    new_line = 1;
    if (token->args[1] != NULL)
        if (ft_strcmp(token->args[1], "-n") == 0)
        {
            new_line = 0;
            i++;
        }
    while (token->args[i] != NULL)
    {
        ft_putstr_fd(token->args[i], STDOUT_FILENO);
            i++;
        if (token->args[i])
            ft_putstr_fd(" ", STDOUT_FILENO);
    }
    if (new_line)
            ft_putstr_fd("\n", STDOUT_FILENO);
    return (EXIT_SUCCESS);
}

int     pwd(t_shell *shell)
{
    char    *pwd;
    int     i;

    pwd = expand_arg(shell, "PWD");
    if (pwd == NULL)
        ft_putchar_fd('\n', STDOUT_FILENO);
    else
    {
        i = 0;
        while (pwd[i] != '\0')
            ft_putchar_fd(pwd[i++], STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
    }
    return (EXIT_SUCCESS);
}

int     env(t_shell *shell)
{
    int     i;

    i = 0;
    while (shell->envc[i] != NULL)
    {
        ft_putstr_fd(shell->envc[i++], STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
    }
    return (EXIT_SUCCESS);
}

int    unset(t_shell *shell, t_token *token)
{
    int	i;
    int len;

	i = 0;
    len = ft_strlen(token->args[1]);
	while (shell->envc[i] != NULL) //search to remove
	{
        if (ft_strncmp(shell->envc[i], token->args[1], len) == 0)
            break ;
        i++;
    }
    if (shell->envc[i] == NULL)
        return (EXIT_FAILURE); //cmd not found?
    free(shell->envc[i]);
    while (shell->envc[i] != NULL)
    {
        shell->envc[i] = shell->envc[i + 1];
        i++;
    }
    shell->envc = (char **) realloc(shell->envc, ((i) * sizeof(char *)));
    //print_2darray(shell->envc);
	return (EXIT_SUCCESS);
}

int    export(t_shell *shell, t_token *token)
{
    int i;
    
    if (token->args[1] == NULL)
        return (env(shell));
    if (ft_strchr(token->args[1], '=') == NULL)
        return (EXIT_SUCCESS);
    i = 0;
    while (shell->envc[i] != NULL)
        i++;
    shell->envc = (char **) realloc(shell->envc, ((i + 2) * sizeof(char *)));
    shell->envc[i] = ft_strdup(token->args[1]);
    shell->envc[i + 1] = NULL;
    // print_2darray(shell->envc);
    return (EXIT_SUCCESS);
}