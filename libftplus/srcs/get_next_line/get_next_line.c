/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:40:40 by junruh            #+#    #+#             */
/*   Updated: 2024/07/19 13:06:17 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*tmpstr;
	char		*result;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(tmpstr);
		free(buf);
		tmpstr = NULL;
		buf = NULL;
		return (NULL);
	}
	result = ft_read_line(fd, buf, tmpstr);
	free(buf);
	if (!result)
		return (NULL);
	tmpstr = ft_cut_line(result);
	return (result);
}

char	*ft_read_line(int fd, char *buf, char *tmpstr)
{
	ssize_t	bytenum;
	char	*tmp;

	bytenum = 1;
	while (bytenum > 0)
	{
		bytenum = read(fd, buf, BUFFER_SIZE);
		if (bytenum < 0)
		{
			free(tmpstr);
			return (NULL);
		}
		if (bytenum == 0)
			break ;
		buf[bytenum] = 0;
		if (!tmpstr)
			tmpstr = ft_strdup_gnl("");
		tmp = tmpstr;
		tmpstr = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (tmpstr);
}

char	*ft_cut_line(char *line)
{
	ssize_t	i;
	char	*tmpstr;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == 0)
		return (NULL);
	tmpstr = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*tmpstr == 0)
	{
		free(tmpstr);
		tmpstr = NULL;
	}
	line[i + 1] = '\0';
	return (tmpstr);
}

/*
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("fd.txt", O_RDONLY);
    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", get_next_line(fd));
    }
    close(fd);
    return (0);
}*/
