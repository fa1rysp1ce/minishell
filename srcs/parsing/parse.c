#include "minishell.h"


int	parse(t_token **list, char **line, t_shell *shell)
{
	char 	**strarr;
	int		arrsize;

	strarr = NULL;
	if (check_input(*line) != 0)
		return (1);
	check_vars(line, shell);
	arrsize = cmd_split(*line, &strarr);
	free(*line);
	if (arrsize < 0)
	{
		rl_clear_history();
		exit(2);
	}
	int i = 0;
	while (strarr[i] != NULL)
	{
		//printf("%s\n", strarr[i]);
		i++;
	}
	fill_list(strarr, list);
	// print_list_inbar(list);
	// print_list(list);
	// free_list(list);
	return (0);
}

int	cmd_split(char const *s, char ***strarr)
{
	int		ccount;

	ccount = ft_ccount(s);
	*strarr = malloc(sizeof(char *) * (ccount + 1));
	if (!strarr[0])
	{
		free((char *)s);
		return (-1);
	}
	if (fill_arr(s, strarr, ccount) < 0)
		return (-1);
	return (ccount);
}

int	fill_list(char **strarr, t_token **list)
{
	add_node(list, strarr, 0);
	eval_str(strarr, list);
	free(strarr);
	return (0);
}
