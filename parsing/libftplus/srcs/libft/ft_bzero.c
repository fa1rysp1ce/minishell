/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:47:35 by junruh            #+#    #+#             */
/*   Updated: 2024/04/23 17:18:16 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <strings.h>
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ss;

	i = 0;
	ss = s;
	while (i < n)
	{
		ss[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	char str[50];

    strcpy(str,"This is string.h library function");

	printf("%s\n", str);
	ft_bzero(str, 3);
	printf("%s\n", str);
	return (0);
}*/
