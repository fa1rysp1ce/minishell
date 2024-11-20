/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:45:28 by ilazar            #+#    #+#             */
/*   Updated: 2024/10/22 13:47:30 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
void	*ft_memset(void *str, int c, size_t n);

#endif
