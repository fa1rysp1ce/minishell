/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:39 by junruh            #+#    #+#             */
/*   Updated: 2024/04/30 18:41:34 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*str;
	unsigned char		ch;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	if (n == 0)
		return (NULL);
	while (n - 1 > 0 && str[i] != ch)
	{
		n--;
		i++;
	}
	if (str[i] == ch)
		return ((void *)&str[i]);
	return (NULL);
}
/*
int	main(void)
{
	const char *str = "01234567";
	
	printf("%s\n", (char *)ft_memchr((const void*)str, 0, 0));
	printf("%s", (char *)memchr((const void *)str, 0, 0));
	return (0);
}*/
