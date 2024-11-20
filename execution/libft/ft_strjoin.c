/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:15:40 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/08 14:47:05 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t				s1_len;
	size_t				s2_len;
	char				*strjoin;
	unsigned int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	strjoin = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (strjoin == NULL)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		strjoin[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 != '\0')
	{
		strjoin[i] = *s2;
		i++;
		s2++;
	}
	strjoin[i] = '\0';
	return (strjoin);
}
