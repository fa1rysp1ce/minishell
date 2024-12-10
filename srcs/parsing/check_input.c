/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:59:24 by junruh            #+#    #+#             */
/*   Updated: 2024/12/10 14:59:27 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_op(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '=')
		return (1);
	return (0);
}

static int	check_ops(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i = skip_quoted(s, i);
		if (s[i] == '|' || s[i] == '=')
		{
			if (i > 0 && (is_op(s[i - 1])))
			{
				free_input(s, s[i]);
				return (1);
			}
		}
		if (s[i] == '<' || s[i] == '>')
		{
			if ((i > 1 && (s[i] == s[i - 1] && s[i] == s[i - 2])) || (i > 0 && (s[i - 1] !=
				s[i] && is_op(s[i - 1]))))
			{
				free_input(s, s[i]);
				return (2);
			}
		}
		i++;
	}
	return (0);
}

//alr checked, rm comments
static int	count_c(char *s, char c)
{
	int i;
	int	count;
	int is_quoted;

	i = 0;
	count = 0;
	is_quoted = 0;
	//printf("Input string: '%s'\n", s);
	while (s[i] != 0)
	{
		if ('"' != c && s[i] == '"' && !is_quoted)
			i = skip_quoted(s, i);
		else if (39 != c && s[i] == 39 && !is_quoted)
			i = skip_quoted(s, i);
		else if (s[i] == c) //&& i != 0 && s[i + 1] != '\0')
		{
			//printf("%c, %d counted\n", s[i], i);
			count++;
			if (count % 2 == 1)
				is_quoted = !is_quoted;
		}
		//printf("%c, %d\n", s[i], i);
		i++;
	}
	//printf("lalalla %d\n", count);
	return (count);
}

static int	check_ends(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '|')
	{
		free_input(s, s[i]);
		return (1);
	}
	if (s[i] == 0)
	{
		free(s);
		return (2);
	}
	while (s[i + 1] != 0)
		i++;
	while (s[i] == ' ')
		i--;
	if (s[i] == '|' || s[i] == '<' || s[i] == '>')
	{
		free_input(s, s[i]);
		return (3);
	}
	return (0);
}

int	check_input(char *s)
{
	if (count_c(s, '"') % 2 != 0)
	{
		free_input(s, '"');
		return (1);
	}
	if (count_c(s, 39) % 2 != 0)
	{
		free_input(s, '\'');
		return (1);
	}
	if (check_ops(s) != 0 || check_ends(s) != 0)
		return (2);
	return (0);
}
