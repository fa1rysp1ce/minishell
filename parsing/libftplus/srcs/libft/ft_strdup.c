/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:16:06 by junruh            #+#    #+#             */
/*   Updated: 2024/04/29 20:53:57 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		len;
	char	*res;
	int		i;

	len = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[len] != 0)
		len++;
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	while (s[i] != 0)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
int	main(void)
{
	char	*str = ft_strdup("weee");
	printf("%s", str);
	free(str);
	return (0);
}*/
