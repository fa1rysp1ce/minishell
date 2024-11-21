/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:49:44 by junruh            #+#    #+#             */
/*   Updated: 2024/05/04 21:34:05 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*ss1;
	unsigned char		*ss2;

	i = 0;
	ss1 = (void *)s1;
	ss2 = (void *)s2;
	if (n == 0)
		return (0);
	while ((unsigned char)ss1[i] == (unsigned char)ss2[i] && i < n - 1)
		i++;
	return ((unsigned char)ss1[i] - (unsigned char)ss2[i]);
}
/*
int	main(void)
{
	char	*s1 = "\xff\0\0\xaa\0\xde\xffMACOSX\xff";
	char	*s2 = "\xff\0\0\xaa\0\xde\x00MBS";

	printf("%d", ft_memcmp((const void *)s1, (const void *)s2, 9));
	return (0);
}*/
