/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:38:10 by inbar             #+#    #+#             */
/*   Updated: 2024/12/10 13:59:34 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *search_in_paths(t_shell *shell, char *arg);
static char	**get_paths(t_shell *shell);
static char	*find_relevant_path(t_shell *shell, char *arg, char **paths, char *cmd);
static void  check_permissions(char *filename, int *status);


/* returns an exectuable command, or null if command wasn't found.
if necessary prints relevant error msg and updates the relevant status variable */
char    *get_cmd_path(t_shell *shell, int *status)
{
    char    *arg;
    char    *cmd_path;
    
    arg = shell->token->args[0];
    if (ft_strrchr(arg, '/') != NULL)
    {
        check_permissions(arg, status);
        return (ft_strdup(arg));
    }
    else
    {
        cmd_path = search_in_paths(shell, arg);
        if (cmd_path == NULL)
            error_msg(arg, "command not found");
        check_permissions(cmd_path, status);
    }
    return (cmd_path);
}

//search the PATH enviorment variable for the given command
static char *search_in_paths(t_shell *shell, char *arg)
{
    char	**paths;
    char	*cmd;
    char    *cmd_path;
    
    paths = get_paths(shell);
    if (paths == NULL)
        return (NULL);
    cmd = ft_strjoin("/", arg);
    if (cmd == NULL)
    {
        free_2d_charr(paths);
        exit_malloc_err(shell);
    }
    cmd_path = find_relevant_path(shell, arg, paths, cmd);
    free_2d_charr(paths);
    return (cmd_path);
}

//retruns a null terminated array of the different paths. or null if error occured
static char	**get_paths(t_shell *shell)
{
	char	**paths;
	char	*env_path;

	paths = NULL;
    env_path = NULL;
	env_path = expand_arg(shell, "PATH");
	if (env_path == NULL)
        return (NULL);
    else
    {
        paths = ft_split(env_path, ':');
        if (paths == NULL)
            exit_malloc_err(shell);
    }
    return (paths);
}

/* given an array of a command and its arguments, and array of paths
returns a freeable string of the command and its path */
static char	*find_relevant_path(t_shell *shell, char *arg, char **paths, char *cmd)
{
	int		i;
	char	*possible_path;

	if (arg == NULL)
        return (NULL);
    i = 0;
    while (paths[i] != NULL)
    {
        possible_path = ft_strjoin(paths[i], cmd);
        if (possible_path == NULL)
        {
            free(cmd);
            free_2d_charr(paths);
            exit_malloc_err(shell);
        }
        if (access(possible_path, F_OK) == 0)
        {
            free(cmd);
            return (possible_path);
        }
        free(possible_path);
        i++;
    }
    free(cmd);
	return (NULL);
}

//check if file exists and its attributes and prints relevant error if any
static void  check_permissions(char *filename, int *status)
{
    struct stat     path_stat;

    // printf("have permissions: %s\n", filename);
    if (filename == NULL)
        return ;

    if (stat(filename, &path_stat) == 0)
    {
        if (S_ISDIR(path_stat.st_mode))
        {
            *status = NON_EXEC;
            error_msg(filename ,"Is a directory");
        }
        else if (S_ISREG(path_stat.st_mode) && (!(path_stat.st_mode & S_IXUSR)))
        {
            *status = NON_EXEC;
            error_msg(filename, "Permission denied");
        }
    }
    else
        error_msg(filename ,"No such file or directory");
}
