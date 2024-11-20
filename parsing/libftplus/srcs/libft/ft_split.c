/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:39:20 by junruh            #+#    #+#             */
/*   Updated: 2024/05/04 21:43:11 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_ccount(char const *s, char c)
{
	int	i;
	int	ccount;

	i = 0;
	ccount = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			ccount++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (ccount);
}

static char	*ft_createsubstr(char const *s, char c, int start)
{
	int		len;
	int		i;
	char	*str;

	len = 0;
	i = 0;
	while (s[len + start] != c && s[len + start] != '\0')
		len++;
	if (len == 0)
		return ("");
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		ccount;
	int		start;
	char	**result;

	ccount = ft_ccount(s, c);
	result = malloc(sizeof(char *) * (ccount + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ccount)
	{
		while (s[j] == c)
			j++;
		start = j;
		while (s[j] != c && s[j] != '\0')
			j++;
		result[i] = ft_createsubstr(s, c, start);
		i++;
	}
	result[i] = NULL;
	return (result);
}
/*
int	main(void)
{
	int i = 0;
	char	**result = ft_split("tripouille", ' ');
	while (i < 4)
	{
		printf("%s\n", result[i]);
		i++;
	}
	free(result);
	return (0);
}*/
