#include "minishell.h"

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

void free_input(char *s, char *statement)
{
	printf("Error\nWrong input: %s\n", statement);
	free(s);
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
	//rl_clear_history();
	exit(1);
}