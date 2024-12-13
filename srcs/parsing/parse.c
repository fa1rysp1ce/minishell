/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:01:05 by junruh            #+#    #+#             */
/*   Updated: 2024/12/13 14:06:41 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_token **list, char **line, t_shell *shell)
{
	char	**strarr;
	int		arrsize;

	strarr = NULL;
	if (check_input(*line) != 0)
		return (1);
	check_vars(line, shell);
	if (line[0][0] == '\0')
		set_exit_status(EXIT_SUCCESS);
	if (check_ops(*line) != 0 || check_ends(*line) != 0)
		return (1);
	arrsize = cmd_split(*line, &strarr);
	free(*line);
	if (arrsize < 0)
	{
		rl_clear_history();
		exit(2);
	}
	if (arrsize == 0 || strarr[0] == NULL)
	{
		set_exit_status(EXIT_SUCCESS);
		return (1);
	}
	fill_list(strarr, list);
	return (0);
}

int	cmd_split(char const *s, char ***strarr)
{
	int		ccount;

	ccount = ft_ccount(s);

	*strarr = malloc(sizeof(char *) * (ccount + 1));
	if (!strarr[0])
	{
		free((char *)s);
		return (-1);
	}
	if (fill_arr(s, strarr, ccount) < 0)
		return (-1);
	return (ccount);
}

int	eval_str(char **strarr, t_token **list)
{
	int	i;

	i = 0;
	while (strarr[i] != NULL)
	{
		if (strarr[i][0] == '|')
			i += pipe_token(strarr, i, list);
		else
			i += handle_commands(strarr, i, list);
	}
	return (i);
}

int	fill_list(char **strarr, t_token **list)
{
	add_node(list, strarr, 0);
	eval_str(strarr, list);
	free(strarr);
	return (0);
}
