/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:41:42 by junruh            #+#    #+#             */
/*   Updated: 2024/04/30 17:00:11 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if ((!dest && !src) || dest == src)
		return (dest);
	d = dest;
	s = src;
	if (d > s)
	{
		i = n;
		while (i--)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char	src[50];
	char	dest[50];

    strcpy(src, "This is string.h library function");

	printf("%s\n", src);
	printf("%s\n", (char *)ft_memmove(dest, src, 9));
	return (0);
}*/
/*
int	main(void)
{
	char *src = "thanks to @apellicc for this test !\r\n";
 	char dst1[0xF0];
 	int size = strlen(src);
 	char *r1 = memmove(dst1, src, size);
 	char *r2 = ft_memmove(dst1, src, size);
	printf("%s\n%s", r1, r2);
	r1 = memmove("", "" - 1, 0);
 	r2 = ft_memmove("", "" - 1, 0);
	printf("%s\n%s", r1, r2);
	return (0);
}*/
