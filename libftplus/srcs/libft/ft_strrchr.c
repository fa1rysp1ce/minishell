/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:48:37 by junruh            #+#    #+#             */
/*   Updated: 2024/04/26 20:38:46 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (c > 255)
		c = c % 256;
	if (c < 0)
		c = 256 + (c % 256);
	i = 0;
	while (s[i] != 0)
		i++;
	while (i > 0)
	{
		if (s[i] == c)
			return ((char *) &s[i]);
		i--;
	}
	if (s[i] == c)
		return ((char *) &s[i]);
	return (NULL);
}
/*
int	main(void)
{
	printf("%s", ft_strrchr("according to all known laws of aviation", 'q'));
	return (0);
}*/
