#include "minishell.h"


static int count_sym(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '|' || s[i] == '<' || s[i] == '>' )
		{
			if ((i > 0 && s[i] != s[i - 1]) || i == 0)
				count++;
		}
		i++;
	}
	return (count);
}

static int	quotes(char const *s, int *i, char c)
{
	int	re;

	re = 0;
	if (*i != 0 && (s[*i - 1]  != ' ' && s[*i - 1] != '|' && s[*i - 1] != '<' && s[*i - 1] != '>'))
		re = 1;
	*i += 1;
	while (s[*i] != '\0' )//&& s[*i] != c)
	{
		if (s[*i] == c && s[*i + 1] != c)
			break; //fix count for consec ""
		*i += 1;
	}
	if (s[*i] == c)
		*i += 1;
	if (s[*i] != 0 && (s[*i + 1]  != ' ' && s[*i + 1] != '|' && s[*i + 1] != '<' && s[*i + 1] != '>'))
		re = 0;
	printf("%d re flag\n", re);
	return (re);
}

int	ft_ccount(char const *s)
{
	int		i;
	int		ccount;
	int		quote_flag;

	i = 0;
	quote_flag = 0;
	ccount = count_sym(s);
	//printf("%d, %c counted\n", ccount, s[i]);
	while (s[i] != '\0')
	{
		printf("%d, %c\n", i, s[i]);
		while (s[i] == ' ' || s[i] == '|' || s[i] == '<' || s[i] == '>')
			i++;
		
		printf("%d quote flag bei %c\n", quote_flag, s[i]);
		if (s[i] != '\0' && quote_flag == 0)
		{
			ccount++;
			printf("%d, %c counted\n", ccount, s[i]);
		}
		quote_flag = 0;
		//printf("dann: %d, %c\n", i, s[i]);
		/*if (s[i + 1] == 39)
			while (s[i] != '\0' && s[i + 1] != 39)
				i++;*/
		while (s[i] != ' ' && s[i] != '|' && s[i] != '<' && s[i] != '>'
			&& s[i] != '\0')
		{
			if (s[i] == '"')
			{
				/*i++;
				while (s[i] != '\0' && s[i] != '"')
					i++;
				if (s[i] == '"')
					i++;*/
				quote_flag = quotes(s, &i, s[i]);
				//continue;
				i++;
			}
			i++;
		}
	}
	printf("%d is count\n", ccount);
	return (ccount);
}

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
		}
		if (s[len + start] != 0)
			len++;
	}
	printf("%d in len\n", len);
	return (len);
}

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
		return ("");
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (j < len)
	{
		if (s[j + start] != '"' && s[j + start] != 39)
		{
			str[i] = s[j + start];
			i++;
		}
		j++;
	}
	str[i] = '\0';
	return (str);
}

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
