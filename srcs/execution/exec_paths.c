/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:38:10 by inbar             #+#    #+#             */
/*   Updated: 2024/11/28 17:28:32 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths(t_shell *shell);
static char	*find_correct_path(t_shell *shell, char *arg, char **paths, char *cmd);

//returns a string containing the full path and name of the command. null if no path exists
//updates the status variable in case absolute path is not executable
char    *get_cmd_path(t_shell *shell, int *status)
{
    char	**paths;
    char    **args;
    char    *cmd_path;
    char	*cmd;
    
    args = shell->token->args;
    if (access(args[0], F_OK) == 0)
    {
        if (access(args[0], X_OK) != 0)
            *status = NON_EXEC;
        return (ft_strdup(args[0]));
    }
    paths = get_paths(shell);
    cmd = ft_strjoin("/", args[0]);
    if (cmd == NULL)
    {
        free_2d_charr(paths);
        exit_malloc_err(shell);
    }
    cmd_path = find_correct_path(shell, args[0], paths, cmd);
    if (cmd_path == NULL)
        free(cmd);
    free_2d_charr(paths);
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
		abort_exec("PATH not found\n", shell);
	paths = ft_split(env_path, ':');
    if (paths == NULL)
        exit_malloc_err(shell);
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
        if (access(possible_path, F_OK | X_OK) == 0)
        {
            free(cmd);
            return (possible_path);
        }
        free(possible_path);
        i++;
    }
    error_msg(arg ,"command not found");
	return (NULL);
}
