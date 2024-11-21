/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:16:31 by junruh            #+#    #+#             */
/*   Updated: 2024/04/23 20:51:45 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int		srclen;
	size_t	i;

	srclen = 0;
	while (src[srclen] != 0)
		srclen++;
	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != 0)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}
/*
int	main(void)
{
	char dst[0];
	char *src = "hallo";
	
	ft_strlcpy(dst, src, 0);

	printf("%s", dst);
	return (0);
}*/
