/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:04:11 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/04 19:54:00 by junruh           ###   ########.fr       */
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
        if (token->args[i] && token->args[i][0] != 0)
            ft_putstr_fd(" ", STDOUT_FILENO);
    }
    if (new_line)
            ft_putstr_fd("\n", STDOUT_FILENO);
    return (EXIT_SUCCESS);
}

int     pwd(void)
{
    char    *pwd;
    char    *buff;
    int     buff_size;

    buff = NULL;
    buff_size = 1024;
    pwd = getcwd(buff, buff_size);
    if (pwd == NULL)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        return (EXIT_FAILURE);
    }
    else
    {
        ft_putstr_fd(pwd, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        free(pwd);
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
    if (token->args[1] == NULL)
        return(EXIT_SUCCESS);
    len = ft_strlen(token->args[1]);
	while (shell->envc[i] != NULL) //search to remove
	{
        if (ft_strncmp(shell->envc[i], token->args[1], len) == 0)
            break ;
        i++;
    }
    if (shell->envc[i] == NULL)
        return (EXIT_SUCCESS); //cmd not found?
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

//must check if env exists and change to it
int    export(t_shell *shell, t_token *token)
{
    int i;
    
    if (token->args[1] == NULL)
        return (env(shell));
    if (ft_strchr(token->args[1], '=') == NULL)
        return (EXIT_SUCCESS);
    if (expand_arg(shell, token->args[1]) == NULL)
    {
        i = 0;
        while (shell->envc[i] != NULL)
            i++;
        shell->envc = (char **) realloc(shell->envc, ((i + 2) * sizeof(char *)));
        shell->envc[i] = ft_strdup(token->args[1]);
        shell->envc[i + 1] = NULL;
    }
    // else
    //     change_env(shell, )
    return (EXIT_SUCCESS);
}