/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:00:26 by junruh            #+#    #+#             */
/*   Updated: 2024/12/10 20:17:56 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		else
			i += handle_commands(strarr, i, list);
	}
	return (i);
}

int	arg_count(char **strarr, int pos)
{
	int	count;
	int i;

	count = 0;
	i = 0;
	while (strarr[i + pos] != NULL && strarr[i + pos][0] != '|')
	{
		if (strarr[i + pos][0] != '<' && strarr[i + pos][0] != '>')
			count++;
		i++;
	}
	return (count);
}
/*
char	*trim_quotes(char **strarr, int pos, t_token **list)
{
	char *result;

	if (strarr[pos][0] == '"')
	{
		result = ft_strtrim(strarr[pos], "\"");
		free(strarr[pos]);
	}
	else if (strarr[pos][0] == '\'')
	{
		result = ft_strtrim(strarr[pos], "\'");
		free(strarr[pos]);
	}
	else
		result = strarr[pos];
	if (!result)
		exit_fill_list(strarr, pos, list);
	return (result);
}*/

char *remove_quotes(char *s)
{
    int		len;
	int		i;
	int		j;
	char	quote_char;

	i = 0;
	j = 0;
    quote_char = '\0';
	len = strlen(s);
    while (j < len)
    {
        char c = s[j];
        if ((c == '"' || c == '\'') && quote_char == '\0')
            quote_char = c;
        else if (c == quote_char)
            quote_char = '\0';
        else
            s[i++] = c;
        j++;
    }
    s[i] = '\0';
	if (ft_strcmp(s, "$EMPTY") == 0)
		return (ft_strdup(""));
    return (s);
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
	//while (i < count)
	while (strarr[pos + i] != NULL && strarr[pos + i][0] != '|')
	{
		if (strarr[pos + i][0] == '<' || strarr[pos + i][0] == '>')
		{
			i += handle_redirec(strarr[pos + i], strarr, pos + i, list);
			//continue ;
			//count--;
		}
		else
			token->args[j++] = remove_quotes(strarr[pos + i]);//trim_quotes(strarr, pos + i, list);
		i++;
	}
	token->args[j] = NULL;
	token->type = CMD;
	return (i);
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

	token = add_node(list, strarr, pos);
	token->args = malloc(sizeof(char *) * 2);
	if (!token->args)
		exit_fill_list(strarr, pos, list);
	token->args[0] = remove_quotes(strarr[pos + 1]);
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

	token = add_node(list, strarr, pos);
	free(strarr[pos]);
	token->type = PIPE;
	add_node(list, strarr, pos);
	return (1);
}
