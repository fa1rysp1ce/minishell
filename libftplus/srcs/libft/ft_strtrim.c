/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:28:31 by junruh            #+#    #+#             */
/*   Updated: 2024/05/04 21:42:07 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	ft_checkchar(char c, char const *set)
{
	int	i;
	int	setlen;

	i = 0;
	setlen = ft_strlen(set);
	while (i < setlen)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static const char	*ft_findstart(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (ft_checkchar(s1[i], set) == 1 && i < (int)ft_strlen(s1))
		i++;
	return (&s1[i]);
}

static const char	*ft_findend(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (ft_checkchar(s1[i], set) == 1 && i >= 0)
		i--;
	return (&s1[i + 1]);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int			i;
	const char	*start;
	const char	*end;
	int			endsize;
	char		*result;

	if (!set)
		return ((char *)s1);
	start = ft_findstart(s1, set);
	end = ft_findend(s1, set);
	endsize = (ft_strlen(start) - ft_strlen(end));
	if (endsize > 0)
		result = malloc(sizeof(char) * (endsize + 1));
	else
		result = malloc(sizeof(char) * 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < endsize)
	{
		result[i] = start[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
int	main(void)
{
	char	*string = ft_strtrim("abcdba", "acb");

	printf("%s", string);
	free(string);
	return (0);
}*/
