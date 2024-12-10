/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbar <inbar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:38:10 by inbar             #+#    #+#             */
/*   Updated: 2024/12/10 05:20:53 by inbar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(t_shell *shell);
static char	*find_correct_path(t_shell *shell, char *arg, char **paths, char *cmd);
// static int  is_absolute(char *path, int *status);
static void  check_permissions(char *filename, int *status);


//returns a string containing the full path and name of the command. null if no path exists
//updates the status variable in case file not executable
char    *get_cmd_path(t_shell *shell, int *status)
{
    char	**paths;
    char    **args;
    char    *cmd_path;
    char	*cmd;
    
    args = shell->token->args;
    // if (is_absolute(args[0], status))
    if (ft_strrchr(args[0], '/') != NULL)
    {
        check_permissions(args[0], status);
        return (ft_strdup(args[0]));
    }
    else
    {
        paths = get_paths(shell);
        if (paths == NULL)
        {
            error_msg(args[0],"command not found");
            return (NULL);
        }

        //search in paths
        // if (args[0][0] != '/')
        // else
            // cmd = ft_strdup(args[0]);
            
        // printf("cmd: %s\n", cmd);
        
        cmd = ft_strjoin("/", args[0]);
        if (cmd == NULL)
        {
            free_2d_charr(paths);
            exit_malloc_err(shell);
        }
        cmd_path = find_correct_path(shell, args[0], paths, cmd);
        free_2d_charr(paths);
        if (cmd_path == NULL)
            error_msg(args[0], "command not found");
        check_permissions(cmd_path, status);
    }
    return (cmd_path);
}

//retruns a null terminated array of paths. or null if error occured
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

//given an array of a command and its arguments, and array of paths
//returns a freeable string of the command and its path 
static char	*find_correct_path(t_shell *shell, char *arg, char **paths, char *cmd)
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

//check if the path is an existing absolute path
// static int  is_absolute(char *path, int *status)
// {
//     if (access(path, F_OK) == 0)
//     {
//         have_permission(path, status);
//         return (1);
//     }
//     return (0);
// }
//check if file exists, check if its executable, check if its a directory
static void  check_permissions(char *filename, int *status)
{
    struct stat     path_stat;
    
    // printf("have permission file path: %s\n", file_path);
    // printf("have permissions: %s\n", filename);
    if (filename == NULL)
        return ;

    else if ((stat(filename, &path_stat) == 0))
        error_msg(filename ,"Is a directory");

    else if (access(filename, F_OK) != 0)
        error_msg(filename ,"No such file or directory");
    
    else if (access(filename, X_OK) != 0)
    {
        *status = NON_EXEC;
        error_msg(filename, "Permission denied");
    }
    
    
    // else
        // error_msg(name ,"command not found");
}
