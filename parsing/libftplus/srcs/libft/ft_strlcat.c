/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:04:27 by junruh            #+#    #+#             */
/*   Updated: 2024/04/30 17:23:45 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	totallen;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	totallen = dstlen + srclen;
	if (dstlen > size || size == 0)
		return (size + srclen);
	while ((i + dstlen) < size - 1 && src[i])
	{
		dst[i + dstlen] = src[i];
		i++;
	}
	if (dstlen < size && size > 0)
		dst[i + dstlen] = '\0';
	return (totallen);
}
/*
int	main(void)
{
	char dst[31] = "hello";
	//char *src = "known laws of aviation";

	printf("%zu", ft_strlcat(dst, "123", 0));

	printf("%s", dst);
	return (0);
}*/
