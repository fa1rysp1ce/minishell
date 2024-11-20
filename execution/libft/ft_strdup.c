/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:41:26 by ilazar            #+#    #+#             */
/*   Updated: 2024/04/26 18:00:46 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	result = (char *) malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
#include <stdio.h>

int	main(void)
{
	char s[] = "abba";

	char *s2 = ft_strdup(s);
	printf("%s	%s\n", s, s2);
	return 0;
}*/
