/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:18:41 by junruh            #+#    #+#             */
/*   Updated: 2024/05/04 21:42:45 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	ft_size(int n)
{
	long	i;
	int		count;

	i = 1;
	count = 0;
	while (n / i != 0)
	{
		count++;
		i *= 10;
	}
	return (count);
}

static char	*ft_convert(long num, char *result, int i)
{
	long	number;

	if (num < 0)
	{
		result[i] = '-';
		i++;
		num = -num;
	}
	number = num;
	while (number / 10 != 0)
	{
		i++;
		number = number / 10;
	}
	while (num / 10 != 0)
	{
		result[i] = (num % 10) + '0';
		num = num / 10;
		i--;
	}
	result[i] = (num % 10) + '0';
	return (result);
}

char	*ft_itoa(int n)
{
	int		strsize;
	char	*result;

	if (n < 0)
		strsize = ft_size(-n) + 1;
	else if (n == 0)
		strsize = 1;
	else
		strsize = ft_size(n);
	result = malloc(sizeof(char) * (strsize + 1));
	if (!result)
		return (NULL);
	result = ft_convert((long)n, result, 0);
	result[strsize] = '\0';
	return (result);
}
/*
int	main(void)
{
	char	*str = ft_itoa(-2147483648);
	printf("%s", str);
	free(str);
	return (0);
}*/	
