/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:59:58 by junruh            #+#    #+#             */
/*   Updated: 2024/12/10 15:00:00 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int count_sym(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		i = skip_quoted(s, i);
		if (s[i] == '|' || s[i] == '<' || s[i] == '>' )
		{
			if ((i > 0 && s[i] != s[i - 1] /*&& '"' != s[i - 1]*/ && '\'' != s[i - 1]) || i == 0)
			{
				count++;
				//printf("%c at %d: count: %d\n", s[i], i, count);
			}
		}
		i++;
	}
	//printf("sym count: %d\n", count);
	return (count);
}
/*
static int	quotes(char const *s, int *i, char c)
{
	int	re;

	re = 0;
	if (*i != 0 && (s[*i - 1]  != ' ' && s[*i - 1] != '|' && s[*i - 1] != '<' && s[*i - 1] != '>'))
		re = 1;
	*i += 1;
	while (s[*i] != '\0' )//&& s[*i] != c)
	{
		if (s[*i] == c && (s[*i + 1] == '\0' || s[*i + 1] != c))
			break;
		*i += 1;
	}
	if (s[*i] == c)
		*i += 1;
	if (s[*i] != 0 && (s[*i + 1]  != ' ' && s[*i + 1] != '|' && s[*i + 1] != '<' && s[*i + 1] != '>'))
		re = 0;
	// printf("%d re flag\n", re);
	return (re);
}*/

int	ft_ccount(char const *s)
{
	int		i;
	int		ccount;

	i = 0;
	ccount = count_sym(s);
	while (s[i] != '\0')
	{
		while (s[i] == ' ' || s[i] == '|' || s[i] == '<' || s[i] == '>'
			)//|| s[i] == '=')
			i++;
		if (s[i] == '"')
			while (s[i] != '\0' && s[i] != '"')
				i++;
		if (s[i] == 39)
			while (s[i] != '\0' && s[i] != 39)
				i++;
		if (s[i] == '"' || s[i] == '\'')
			i++;
		if (s[i] != '\0')
		{
			ccount++;
			//printf("%c at %d: count: %d\n", s[i], i, ccount);
		}
		while (s[i] != ' ' && s[i] != '|' && s[i] != '<' && s[i] != '>'
			/*&& s[i] != '=' */&& s[i] != '\0')
			i++;
	}
	//printf("ccount : %d\n", ccount);
	return (ccount);
}

/*
int	ft_ccount(char const *s)
{
	int		i;
	int		ccount;
	int		quote_flag;

	i = 0;
	quote_flag = 0;
	ccount = count_sym(s);
	//printf("%d, %c counted\n", ccount, s[i]);
	printf("%s\n", s);
	while (s[i] != '\0')
	{
		printf("%d, \n", i);
		while (s[i] == ' ' || s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			i++;
			printf("%d, %c\n", i, s[i]);
		}
		// printf("%d quote flag bei %c\n", quote_flag, s[i]);
		if (s[i] != '\0' && quote_flag == 0)
		{
			ccount++;
			// printf("%d, %c counted\n", ccount, s[i]);
		}
		quote_flag = 0;
		//printf("dann: %d, %c\n", i, s[i]);
		// hier tsern anfang if (s[i + 1] == 39)
			while (s[i] != '\0' && s[i + 1] != 39)
				i++; // hier mit stern wieder
		while (s[i] != ' ' && s[i] != '|' && s[i] != '<' && s[i] != '>'
			&& s[i] != '\0')
		{
			if (s[i] == '"')
			{
				// hier tsern anfang i++;
				while (s[i] != '\0' && s[i] != '"')
					i++;
				if (s[i] == '"')
					i++; // hier auch stern
				if (s[i + 1] == s[i])
					ccount++;
				else
					quote_flag = quotes(s, &i, s[i]);
				//continue;
				//i++;
			}
			printf("%d, %c\n", i, s[i]);
			i++;
		}
	}
	//printf("%d is count\n", ccount);
	return (ccount);
}*/

/*
int	ft_ccount(char const *s)
{
	int		i;
	int		ccount;
	int		d_quotes;

	i = 0;
	d_quotes = 0;
	ccount = count_sym(s);
	//printf("%d, %c counted\n", ccount, s[i]);
	while (s[i] != '\0')
	{
		printf("%d, %c\n", i, s[i]);
		printf("d_quotes vorher: %d\n", d_quotes);
		if (s[i] == '"')
		{
			d_quotes = !d_quotes;
			printf("d_quotes: %d\n", d_quotes);
			i++;
			//continue ;
			// hier * while (s[i] != '\0' && s[i] != '"')
				i++;
			if (s[i] == '"')
				i++; //hier *
		}
		while (!d_quotes && (s[i] == ' ' || s[i] == '|' || s[i] == '<' || s[i] == '>' ))
			i++;
		if (s[i] != '\0' && !d_quotes)
		{
			ccount++;
			printf("%d, %c counted\n", ccount, s[i]);
		}
		//printf("dann: %d, %c\n", i, s[i]);
		// hier *  if (s[i + 1] == 39)
			while (s[i] != '\0' && s[i + 1] != 39)
				i++; // hier *
		while ((s[i] != ' ' && s[i] != '|' && s[i] != '<' && s[i] != '>'
			&& s[i] != '\0') || (d_quotes && (s[i] != '"' && s[i] != 39)))
			i++;
	}
	printf("%d is count\n", ccount);
	return (ccount);
}*/


static int	getslen(char const *s, int start)
{
	int	len;

	len = 0;
	if ((s[len + start] == '<' || s[len + start] == '>') 
		&& (s[len + start] == s[len + start + 1]))
		return (2);
	else if (s[len + start] == '|' || s[len + start] == '<' || s[len + start] == '>')
		return (1);
	while (s[len + start] != '\0' && s[len + start] != ' ' && s[len + start]
		!= '<' && s[len + start] != '>' && s[len + start] != '|')
	{
		//printf("%c\n", s[len + start]);
		if (s[len + start] == '"')
		{
			while (s[len + start] != '\0' && s[len + start + 1] != '"')
				len++;
			len += 1; //THIS from chatgpt
		}
		if (s[len + start] == 39)
		{
			while (s[len + start] != '\0' && s[len + start + 1] != 39)
				len++;
			len += 1;
		}
		if (s[len + start] != 0)
			len++;
	}
	// printf("%d in len\n", len);
	return (len);
}

/*static int	valid_quote(const char *s, int j, int start)
{
	int i;
	int	count;
	int is_quoted;

	i = 0;
	count = 0;
	is_quoted = 0;
	if ('"' != s[j + start] && 39 != s[j + start])
		return (1);
	//printf("Input string: '%s'\n", s);
	while (i <= j + start)
	{
		if ('"' != s[j + start] && s[i] == '"' && !is_quoted)
		{
			i++;
			//printf("hihi\n");
			while (s[i] != '"' && s[i] != 0)
				i++;
		}
		else if (39 != s[j + start] && s[i] == 39 && !is_quoted)
		{
			i++;
			while (s[i] != 39 && s[i] != 0)
				i++;
		}
		else if (('"' != s[j + start] && s[i] == '"') || (39 != s[j + start] && s[i] == 39))//&& i != 0 && s[i + 1] != '\0')
		{
			//printf("%c, %d counted\n", s[i], i);
			count++;
			if (count % 2 == 1)
				is_quoted = !is_quoted;
		}
		//printf("%c, %d\n", s[i], i);
		i++;
	}
	printf("lalalla %d at %c, index: %d\n", is_quoted, s[j + start], j + start);
	return (is_quoted);
}
*/


static char	*ft_createsubstr(char const *s, int start)
{
	int		len;
	int		i;
	int		j;
	char	*str;

	len = getslen(s, start);
	i = 0;
	j = 0;
	if (len == 0)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (j < len)
	{
		//if ((valid_quote(s, j, start) == 1))//&& (i != 0 && j != len - 1)) // (((s[j + start] != '"') && (s[j + start] != 39)) || (i != 0 && j != len - 1))
		//{
		//	printf("lala\n");
			str[i] = s[j + start];
			i++;
		//}
		j++;
	}
	str[i] = '\0';
	return (str);
}
/*
//check out the next two again perplexity helped
static int is_quote(char c)
{
    return (c == '"' || c == '\'');
}

static char *ft_createsubstr(char const *s, int start)
{
    int len = getslen(s, start);
    char *str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return NULL;

    int i = 0, j = 0;
    char quote_char = '\0';

    while (j < len)
    {
        char c = s[j + start];

        if (is_quote(c) && quote_char == '\0')
        {
            quote_char = c;  // Start of a quoted section
        }
        else if (c == quote_char)
        {
            quote_char = '\0';  // End of a quoted section
        }
        else
        {
            str[i++] = c;  // Copy character if not a quote or inside quotes
        }

        j++;
    }

    str[i] = '\0';
    return str;
}*/



int	fill_arr(char const *s, char ***strarr, int ccount)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (i < ccount)
	{
		while (s[j] == ' ')
			j++;
		start = j;
		j += getslen(s, start);
		strarr[0][i] = ft_createsubstr(s, start);
		if (strarr[0][i] == NULL)
		{
			free_split(*strarr, i, (char *)s);
			return (-1);
		}
		i++;
	}
	strarr[0][i] = NULL;
	return (0);
}
