/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:04:11 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/13 14:31:14 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_newline(char *arg, int *new_line);

int	pwd(void)
{
	char	*pwd;
	char	*buff;
	int		buff_size;

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

int	env(t_shell *shell)
{
	int	i;

	if (shell->token->args[1] != NULL)
	{
		error_msg(shell->token->args[1], "No such file or directory");
		return (NO_CMD);
	}
	i = 0;
	while (shell->envc[i] != NULL)
	{
		ft_putstr_fd(shell->envc[i++], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}

int	cd(t_shell *shell)
{
	t_token	*token;

	token = shell->token;
	if (token->args[1] != NULL && token->args[2] != NULL)
	{
		error_msg(token->args[0], "too many arguments");
		return (EXIT_FAILURE);
	}
	if (token->args[1] == NULL || ft_strcmp(token->args[1], "~") == 0)
		return (cd_home(shell));
	if (ft_strcmp(token->args[1], "..") == 0)
		return (cd_parent_dir(shell));
	if (ft_strcmp(token->args[1], "-") == 0)
		return (prev_dir(shell));
	return (cd_path(shell, shell->token->args[1]));
}

//{"echo", "-n" / "", "txt...", "txt...", "null"}
int	echo(t_token *token)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (token->args[1] != NULL)
	{
		while (token->args[i] != NULL && ft_strncmp(token->args[i], "-n",
				2) == 0)
		{
			if (!is_newline(token->args[i], &new_line))
				break ;
			i++;
		}
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

// for echo:
// returns 1 if 3rd char and on of arg consists of only chars of 'n'
static int	is_newline(char *arg, int *new_line)
{
	int	i;

	i = 2;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	*new_line = 0;
	return (1);
}
