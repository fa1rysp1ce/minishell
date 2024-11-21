/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:32:16 by junruh            #+#    #+#             */
/*   Updated: 2024/04/29 17:14:45 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] != 0 && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i] != 0 && little[j] != 0
			&& (i + j) < len)
		{
			j++;
		}
		if (little[j] == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char	*big = "according to all known laws of aviation";
	const char	*little = "bu";

	printf("%s", ft_strnstr(big, little, 50));
	return (0);
}*/
/*
int main(void)
{
	char *s1 = "oh no not the empty string !";
 	char *s2 = "";
 	size_t max = 0;
// 	char *i1 = strnstr(s1, s2, max);
 	char *i2 = ft_strnstr(s1, s2, max);
	printf("%s", i2);
	return (0);
}*/
