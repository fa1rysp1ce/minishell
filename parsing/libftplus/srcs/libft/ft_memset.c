/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:40:46 by junruh            #+#    #+#             */
/*   Updated: 2024/04/23 16:34:25 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = str;
	while (i < n)
	{
		s[i] = c;
		i++;
	}
	return (str);
}
/*
int	main(void)
{
	char str[50];

    strcpy(str,"This is string.h library function");

	printf("%s\n", str);
	printf("%s\n", (char *)memset(str, '$', 10));
	printf("%s\n", (char *)ft_memset(str, '$', 10));
	return (0);
}*/
