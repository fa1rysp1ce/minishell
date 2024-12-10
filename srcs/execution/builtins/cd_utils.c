/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:49:37 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/10 18:04:09 by ilazar           ###   ########.fr       */
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

int cd_home(t_shell *shell)
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


int cd_parent_dir(t_shell *shell)
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

int cd_path(t_shell *shell ,char *path)
{
    char    *pwd;
    char    *buff;
    int     buff_size;
    char    *src;
    
    buff = NULL;
    buff_size = 1024;
    if (path[0] == '~')
        return (cd_path_tilde(shell, path));
    if (chdir(path) == 0)
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
        error_msg(path, strerror(errno));
    return (EXIT_FAILURE);
}

int cd_path_tilde(t_shell *shell ,char *path)
{
    int     status;
    char    *full_path;
    char    *no_tilde;

    if (expand_arg(shell, "HOME") == NULL)
    {
        ft_putstr_fd("Minishell: cd: HOME not set\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    no_tilde = ft_strdup(&path[1]);
    full_path = ft_strjoin(expand_arg(shell, "HOME"), no_tilde);
    free(no_tilde);
    if (chdir(full_path) == 0)
        status = cd_path(shell, full_path);
    else
    {
        status = EXIT_FAILURE;
        error_msg(path, strerror(errno));
    }
    free(full_path);
    return (status);
    }

int     prev_dir(t_shell *shell)
{
    char    *pwd;
    char    *buff;
    int     buff_size;

    buff = NULL;
    buff_size = 1024;
    pwd = getcwd(buff, buff_size);  
    if (shell->prev_dir != NULL)
    {
        if (cd_path(shell, shell->prev_dir) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        ft_putstr_fd(shell->prev_dir, STDIN_FILENO);
        ft_putstr_fd("\n", STDIN_FILENO);
        free(shell->prev_dir);
        shell->prev_dir = pwd;
        return (EXIT_SUCCESS);
    }
    ft_putstr_fd(pwd, STDIN_FILENO);
    ft_putstr_fd("\n", STDIN_FILENO);
    shell->prev_dir = pwd;
    return (EXIT_SUCCESS);
}

