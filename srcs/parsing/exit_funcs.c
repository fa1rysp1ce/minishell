#include "minishell.h"

void	exit_variables(char *str)
{
	perror("malloc failure");
	free(str);
	rl_clear_history();
	exit(1);
}

void	free_split(char **arr, int last, char *s)
{
	int	i;

	i = 0;
	free(s);
	while (i < last)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

int free_input(char *s, char c)
{
	printf("minishell: syntax error near unexpected token '%c'\n", c);
	free(s);
	return (1);
}

void	exit_fill_list(char **strarr, int pos, t_token **list)
{
	printf("Malloc failure\n");
	while (strarr[pos] != NULL)
	{
		free(strarr[pos]);
		pos++;
	}
	free(strarr);
	free_list(list);
	rl_clear_history();
	exit(1);
}