/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:04:14 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/03 16:21:12 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//make a picture of evn


static char	**picture_env(char **env);
static	char **picture_env_vars(char **env, char **envc);

void    init_shell(t_shell *shell, char **env)
{
	shell->envc = picture_env(env);
	shell->execute = NULL;
	shell->head_token = NULL;
	shell->token = NULL;
	shell->last_exit_status = EXIT_SUCCESS;
}

//create a copy of enviorment vars for later use
static char	**picture_env(char **env)
{
	int	i;
	char 	**envc;

	i = 0;
	while (env[i] != NULL)
		i++;
	envc = (char **) malloc(sizeof(char *) * (i + 1));
	if (envc == NULL)
		exit_error("malloc");
	return (picture_env_vars(env, envc));
}
	
static	char **picture_env_vars(char **env, char **envc)
{
	int	i;
	int	var_len;
	
	i = 0;
	while (env[i] != NULL)
	{
		var_len = 0;
		while (env[i][var_len] != '\0')
			var_len++;
		envc[i] = (char *) malloc(sizeof(char) * (var_len + 1));
			if (envc[i] == NULL)
			{
				free_2d_charr(envc);
				exit_error("malloc");
			}
		var_len = 0;
		while (env[i][var_len] != '\0')
		{
			envc[i][var_len] = env[i][var_len];
			var_len++;
		}	
		envc[i++][var_len] = '\0';
	}
	envc[i] = NULL;
	return (envc);
}

//takes an envirment argument, for example $USER ("USER") and returns its value
//returns NULL if error occures 
char	*expand_arg(t_shell *shell, char *arg)
{
	char	**env;
	int	arg_len;
	int	i;
	int	j;
	char *equal;

	env = shell->envc;
	equal = ft_strjoin(arg, "=");
	if (equal == NULL)
		exit_malloc_err(shell);
	arg_len = ft_strlen(equal);
	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], equal, arg_len) != 0)
		i++;
	free(equal);
	if (env[i] == NULL)
		return (NULL);
	j = 0;
	while (env[i][j] != '\0' && env[i][j] != '=')
		j++;
	if (env[i][j] == '\0')
		return (NULL);
	j++;
	return (shell->envc[i] + j);
}

