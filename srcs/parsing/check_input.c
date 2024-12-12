/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:59:24 by junruh            #+#    #+#             */
/*   Updated: 2024/12/12 17:58:12 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ops2(char *s, int i)
{
	int	j;

	j = i;
	if ((i > 1 && (s[i] == s[i - 1] && s[i] == s[i - 2])) || (i > 0
			&& (s[i - 1] != s[i] && is_op(s[i - 1]))))
	{
		free_input(s, s[i]);
		return (1);
	}
	while (j > 0 && s[j] == ' ')
		j--;
	if ((s[j] == '>' || s[j] == '<') && j != i)
	{
		free_input(s, s[i]);
		return (2);
	}
	j = i;
	while (s[j] == ' ')
		j++;
	if ((s[j] == '>' || s[j] == '<') && j != i)
	{
		free_input(s, s[i]);
		return (2);
	}
	return (0);
}

int	check_ops(char *s)
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
			if (check_ops2(s, i) != 0)
			{
				return (2);
			}
		}
		i++;
	}
	return (0);
}

static int	count_c(char *s, char c)
{
	int	i;
	int	count;
	int	is_quoted;

	i = 0;
	count = 0;
	is_quoted = 0;
	while (s[i] != 0)
	{
		if ('"' != c && s[i] == '"' && !is_quoted)
			i = skip_quoted(s, i);
		else if (39 != c && s[i] == 39 && !is_quoted)
			i = skip_quoted(s, i);
		else if (s[i] == c)
		{
			count++;
			if (count % 2 == 1)
				is_quoted = !is_quoted;
		}
		i++;
	}
	return (count);
}

int	check_ends(char *s)
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
