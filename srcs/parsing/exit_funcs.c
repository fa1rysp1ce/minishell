/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:00:14 by junruh            #+#    #+#             */
/*   Updated: 2024/12/12 18:06:21 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_variables(char *str)
{
	perror("malloc failure");
	free(str);
	rl_clear_history();
	exit(1);
}

void	free_split(char **arr, int last, char *s)
{
	int	i;

	i = 0;
	free(s);
	while (i < last)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

int	free_input(char *s, char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '",
		STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	set_exit_status(EXIT_FAILURE);
	free(s);
	return (1);
}

void	exit_fill_list(char **strarr, int pos, t_token **list)
{
	printf("Malloc failure\n");
	while (strarr[pos] != NULL)
	{
		free(strarr[pos]);
		pos++;
	}
	free(strarr);
	free_list(list);
	rl_clear_history();
	exit(1);
}
