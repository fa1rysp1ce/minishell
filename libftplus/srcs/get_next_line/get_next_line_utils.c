/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:22:26 by junruh            #+#    #+#             */
/*   Updated: 2024/07/19 13:04:21 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}*/

/*char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;
	int		s1len;
	int		s2len;

	i = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!str)
		return (NULL);
	while (i < s1len)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2len)
	{
		str[s1len + i] = s2[i];
		i++;
	}
	str[s1len + i] = '\0';
	return (str);
}*/

char	*ft_strdup_gnl(const char *s)
{
	int		len;
	char	*res;
	int		i;

	len = 0;
	i = 0;
	while (s[len] != 0)
		len++;
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	while (s[i] != 0)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

/*char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	if (ft_strlen(s) <= start)
	{
		substr = ft_strdup("");
		return (substr);
	}
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != 0)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}*/

/*char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (c > 255)
		c = c % 256;
	if (c < 0)
		c = 256 + (c % 256);
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}*/
