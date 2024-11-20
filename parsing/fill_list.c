#include "minishell.h"

int	eval_str(char **strarr, t_token **list)
{
	int	i;

	i = 0;
	while (strarr[i] != NULL)
	{
		//printf("iteration index: %d\n", i);
		if (strarr[i][0] == '|')
			i += pipe_token(strarr, i, list);
		/*else if (strarr[i][0] == '<' || strarr[i][0] == '>')
		{
			if (strarr[i][0] == '<')
				i += handle_input(strarr[i], strarr, i, list);
			else if (strarr[i][0] == '>')
				i += handle_output(strarr[i], strarr, i, list);
		}*/
		else
			i += handle_commands(strarr, i, list);
	}
	return (i);
}

int	arg_count(char **strarr, int pos)
{
	int	count;

	count = 0;
	while (strarr[count + pos] != NULL && strarr[count + pos][0] != '|')
	{
		count++;
	}
	return (count);
}

int	handle_commands(char **strarr, int pos, t_token **list)
{
	t_token	*token;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	token = find_last(list);
	count = arg_count(strarr, pos);
	token->args = malloc(sizeof(char *) * (count + 1));
	if (!token->args)
		exit_fill_list(strarr, pos, list);
	while (i < count)
	{
		if (strarr[pos + i][0] == '<' || strarr[pos + i][0] == '>')
		{
			i += handle_redirec(strarr[pos + i], strarr, pos + i, list);
		}
		else
			token->args[j++] = strarr[pos + i];
		i++;
	}
	token->args[i] = NULL;
	token->type = CMD;
	return (count);
}
/*
char *	handle_heredoc(t_token **list)
{
	int	fd;

	fd = 0;
	fd = open("heredoc.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
}*/

int	handle_redirec(char *str, char **strarr, int pos, t_token **list)
{
	t_token *token;

	token = add_node(list);
	token->args = malloc(sizeof(char *) * 2);
	if (!token->args)
		exit_fill_list(strarr, pos, list);
	token->args[0] = strarr[pos + 1];
	token->args[1] = NULL;
	if (str[0] == '<' && str[1] != '<')
		token->type = IN;
	else if (str[0] == '<' && str[1] == '<')
		token->type = HDOC;
	else if (str[0] == '>' && str[1] != '>')
		token->type = OUT;
	else if (str[0] == '>' && str[1] == '>')
		token->type = OUT_APP;
	free(str);
	return (1);
}
/*
int	handle_output(char *str, char **strarr, int pos, t_token **list)
{
	t_token *token;
	int		fd;

	token = find_last(list);
	if (token->output != NULL)
		free(token->output);
	token->output = strarr[pos + 1];
	if (str[1] == '>')
	{
		token->is_append = 1;
		fd = open(strarr[pos + 1], O_RDWR | O_CREAT, 0666);
	}	
	else
	{
		token->is_append = 0;
		fd = open(strarr[pos + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	}
	close(fd);
	free(str);
	return (2);
}*/

int	pipe_token(char **strarr, int pos, t_token **list)
{
	t_token *token;

	token = add_node(list);
	free(strarr[pos]);
	token->type = PIPE;
	add_node(list);
	return (1);
}