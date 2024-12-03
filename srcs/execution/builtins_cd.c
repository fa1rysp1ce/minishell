/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:49:37 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/03 17:39:34 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Handling absolute paths:
Paths starting with '/' (e.g., /home/user/documents)
Handling relative paths:
Paths not starting with '/' (e.g., documents/projects)

'..' (parent directory) 
'.' (current directory)
'~' to represent the user's home directory
*/

static int cd_home(t_shell *shell) //if getcwd fails - no solution
{
    char    *buff;
    int     buff_size;
    char    *pwd;
    char    *src;
    
    buff = NULL;
    buff_size = 1024;
    if (expand_arg(shell, "HOME") != NULL)
    {
        chdir(expand_arg(shell, "HOME"));
        pwd = getcwd(buff, buff_size);
        src = ft_strdup(expand_arg(shell, "PWD"));
        change_env(shell, src, "OLDPWD");
        free(src);
        change_env(shell, pwd, "PWD");
        free(pwd);
        return (EXIT_SUCCESS);
    }
    else
        ft_putstr_fd("Minishell: cd: HOME not set\n", STDERR_FILENO);
    return (EXIT_FAILURE);
}


static int cd_parent_dir(t_shell *shell)
{
    char    *pwd;
    char    *buff;
    int     buff_size;

    buff = NULL;
    buff_size = 1024;
    pwd = getcwd(buff, buff_size);
    if (pwd == NULL)
        return (EXIT_FAILURE);
    if (chdir("..") == 0)
    {
        change_env(shell, pwd, "OLDPWD");
        free(pwd);
        pwd = getcwd(buff, buff_size);
        if (pwd == NULL)
            return (EXIT_FAILURE);
        change_env(shell, pwd, "PWD");
        free(pwd);
        return (EXIT_SUCCESS);
    }
    else
        error_msg(expand_arg(shell, "OLDPWD"), strerror(errno));
    return (EXIT_FAILURE);
}

static int cd_path(t_shell *shell)
{
    char    *pwd;
    char    *buff;
    int     buff_size;
    t_token *token;
    char    *src;
    
    token = shell->token;
    buff = NULL;
    buff_size = 1024;
    if (chdir(token->args[1]) == 0)
    {
        pwd = getcwd(buff, buff_size);
        if (pwd == NULL)
            return (EXIT_FAILURE);
        src = ft_strdup(expand_arg(shell, "PWD"));
        change_env(shell, src, "OLDPWD");
        free(src);
        change_env(shell, pwd, "PWD");
        free(pwd);
        return (EXIT_SUCCESS);
    }
    else
        error_msg(token->args[1], strerror(errno));
    return (EXIT_FAILURE);
}


//problem with if (token->args[2] != NULL) -- cus it might no be null but full of random trash
int     cd(t_shell *shell)
{
    t_token *token;
    
    token = shell->token;
    if (token->args[2] != NULL)
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
        return(EXIT_FAILURE);
    }
    if (token->args[1] == NULL || ft_strcmp(token->args[1], "~") == 0)
        return (cd_home(shell));
    if (ft_strcmp(token->args[1], "..") == 0)
        return (cd_parent_dir(shell));
    return (cd_path(shell));
}
