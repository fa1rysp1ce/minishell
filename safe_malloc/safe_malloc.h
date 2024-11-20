#ifndef SAFE_MALLOC_H
# define SAFE_MALLOC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
//# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PTR 0
# define FILE 1

typedef struct s_node
{
	void	*ptr;
	int		file;
	void	*next;
} t_node;

void	*safe_malloc(t_node **node, void *ptr, int file);
void	safe_free(t_node **list);
void	safe_m_print(t_node **list);

#endif