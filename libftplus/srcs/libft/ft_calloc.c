/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:13:11 by junruh            #+#    #+#             */
/*   Updated: 2024/04/30 16:29:08 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

#define INT_MAX 2147483647
#define INT_MIN -2147483648

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*memory;
	long	result;

	result = nmemb * size;
	if (result > INT_MAX || result < INT_MIN)
		return (NULL);
	memory = malloc(result);
	if (memory == NULL)
		return (memory);
	ft_bzero(memory, result);
	return ((void *)memory);
}
/*
int	main(void)
{
	int *a;

	a = ft_calloc(10, 8);
	printf("%p", a);
	free(a);
	return (0);
}*/
