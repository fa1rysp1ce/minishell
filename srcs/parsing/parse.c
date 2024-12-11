/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:01:05 by junruh            #+#    #+#             */
/*   Updated: 2024/12/11 19:00:58 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	parse(t_token **list, char **line, t_shell *shell)
{
	char 	**strarr;
	int		arrsize;

	strarr = NULL;
	//printf("1\n");
	if (check_input(*line) != 0)
		return (1);
	//printf("2\n");
	check_vars(line, shell);
	if (check_ops(*line) != 0 || check_ends(*line) != 0)
		return (1);
	//printf("new line: %s \n", *line);
	//printf("3\n");
	arrsize = cmd_split(*line, &strarr);
	//printf("4\n");
	free(*line);
	if (arrsize < 0)
	{
		rl_clear_history();
		exit(2);
	}
	if (arrsize == 0)
	{
		set_exit_status(EXIT_SUCCESS);
		return (1);
	}
	/*int i = 0;
	while (strarr[i] != NULL)
	{
		printf("%s\n", strarr[i]);
		i++;
	}*/
	fill_list(strarr, list);
	return (0);
}

int	cmd_split(char const *s, char ***strarr)
{
	int		ccount;

	//if (s[0] == '\0')
	//	return (0);
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

int	fill_list(char **strarr, t_token **list)
{
	add_node(list, strarr, 0);
	eval_str(strarr, list);
	free(strarr);
	return (0);
}
