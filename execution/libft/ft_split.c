/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 00:54:44 by ilazar            #+#    #+#             */
/*   Updated: 2024/05/02 00:25:59 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_all(char **strs);
static int	split_to_words(char **strs, const char *s, char c);
static char	*make_word(const char *s, char c);

static int	count_words(const char *s, char c)
{
	int	inside_word;
	int	words;

	words = 0;
	inside_word = 0;
	while (*s != '\0')
	{
		if (*s == c)
			inside_word = 0;
		if (*s != c && inside_word == 0)
		{
			inside_word = 1;
			words++;
		}
		s++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**strs;

	if (s == NULL)
		return (0);
	words = count_words(s, c);
	strs = (char **) malloc(sizeof(char *) * (words + 1));
	if (strs == NULL)
		return (NULL);
	if (!split_to_words(strs, s, c))
	{
		free_all(strs);
		return (NULL);
	}
	strs[words] = 0;
	return (strs);
}

static int	split_to_words(char **strs, const char *s, char c)
{
	unsigned int	inside;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	inside = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			inside = 0;
		else if (s[i] != c)
		{
			if (inside == 0)
			{
				strs[j] = make_word(&s[i], c);
				if (strs[j] == NULL)
					return (0);
				j++;
			}
			inside = 1;
		}
		i++;
	}
	return (1);
}

static char	*make_word(const char *s, char c)
{
	unsigned int	i;
	char			*word;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	word = (char *) malloc(sizeof(char) * i + 1);
	if (word == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0' && *s != c)
	{
		word[i] = *s;
		i++;
		s++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_all(char **strs)
{
	unsigned int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/*
#include <stdio.h>
int	main(int ac, char **av)
{
	(void) ac;

	char **str;
	int	i;

	i = 0;
	str = ft_split(av[1], av[2][0]);
	while (str[i] != NULL)
	{
		printf("%s	%ld\n", str[i], ft_strlen(str[i]));
		i++;
	}
	if (str[i] == NULL)
		printf("null\n");
	return (0);
}*/
