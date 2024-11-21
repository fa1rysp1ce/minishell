/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:00:21 by junruh            #+#    #+#             */
/*   Updated: 2024/04/30 16:39:48 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
/*
static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;
	int		s1len;
	int		s2len;

	i = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!str)
		return (NULL);
	while (i < s1len)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2len)
	{
		str[s1len + i] = s2[i];
		i++;
	}
	str[s1len + i] = '\0';
	return (str);
}
/*
int	main(void)
{
	char	*str = ft_strjoin("what are you doing in my ", "swamp");
	printf("%s", str);
	free(str);
	return (0);
}*/
