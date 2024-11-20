#include "minishell.h"
// qoute version of ccount
int	ft_ccount(char const *s)
{
	int		i;
	int		ccount;

	i = 0;
	ccount = count_sym(s);
	//printf("%d, %c counted\n", ccount, s[i]);
	while (s[i] != '\0')
	{
		printf("%d, %c\n", i, s[i]);
		while (s[i] == ' ' || s[i] == '|' || s[i] == '<' || s[i] == '>')
			i++;
		if (s[i] != '\0')
		{
			ccount++;
			printf("%d, %c counted\n", ccount, s[i]);
		}
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '"')
				i++;
			if (s[i] == '"')
				i++;
		}
		//printf("dann: %d, %c\n", i, s[i]);
		if (s[i + 1] == 39)
			while (s[i] != '\0' && s[i + 1] != 39)
				i++;
		while (s[i] != ' ' && s[i] != '|' && s[i] != '<' && s[i] != '>'
			&& s[i] != '\0')
			i++;
	}
	printf("%d is count\n", ccount);
	return (ccount);
}
/*
static int	ft_ccount(char const *s)
{
	int		i;
	int		ccount;
	char	c;

	i = 0;
	ccount = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ' || s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			c = s[i];
			while (s[i] == c)
				i++;
		}
		if (s[i] != '\0')
		{
			ccount++;
			printf("%c\n", s[i]);
		}
		if (s[i - 1] == '|' || s[i - 1] == '<' || s[i - 1] == '>')
		{
			//ccount++;
			printf("%c\n", s[i]);
		}
		while (s[i] != ' ' && s[i] != '|' && s[i] != '<' && s[i] != '>'
			&& s[i] != '\0')
			i++;
	}
	printf("%d\n", ccount);
	return (ccount);
}*/

static int count_sym(char const *s)
{
	int	i;
	int j;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			j = i - 1;
			while (j >= 0 && s[j] != '|' && s[j] != '=')
				j--;
			if (s[j] != '=')
				count += 2;
		}
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')// || s[i] == '=')
		{
			if (i > 0 && s[i] != s[i - 1])
				count++;
		}
		i++;
	}
	//printf("%d sym\n", count);
	return (count);
}

static int	ft_ccount(char const *s)
{
	int		i;
	int		ccount;

	i = 0;
	ccount = count_sym(s);
	while (s[i] != '\0')
	{
		if (s[i + 1] == '"')
			while (s[i] != '\0' && s[i + 1] != '"')
				i++;
		if (s[i + 1] == 39)
			while (s[i] != '\0' && s[i + 1] != 39)
				i++;
		while (s[i] == ' ' || s[i] == '|' || s[i] == '<' || s[i] == '>'
			)//|| s[i] == '=')
			i++;
		if (s[i] != '\0')
			ccount++;
		while (s[i] != ' ' && s[i] != '|' && s[i] != '<' && s[i] != '>'
			/*&& s[i] != '=' */&& s[i] != '\0')
			i++;
	}
	//printf("%d\n", ccount);
	return (ccount);
}

static int	handle_rds(char const *s, int start)
{
	int	len;

	len = 0;
	if (s[len + start] == s[len + start + 1])
		len++;
	/*else if (s[len + start + 1] == '<' || s[len + start + 1] == '>')
	{
		printf("parse error with redirections\n");
		return (-1);
	}
	if (s[len + start] == s[len + start + 1])
	{
		printf("parse error with redirections\n");
		return (-1);
	}*/
	return (len);
}

static int	check_last_word(char const *s, int pos)
{
	int	i;

	i = pos - 1;
	while (i >= 0 && s[i] == ' ')
	{
		i--;
	}
	if (i == 0 || s[i] == '|')
		return (1);
	return (0);
}

static int	getslen2(char const *s, int start, int len, int equal_no)
{
	while (s[len + start] != '\0' && s[len + start] != ' ' && s[len + start]
		!= '<' && s[len + start] != '>' && s[len + start] != '|')
		//&& s[len + start] != '=')
	{
		if (s[len + start] == '=' && s[len + start + 1] != '\0' && s[len + 
			start + 1] != ' ' && !is_op(s[len + start + 1]) && equal_no == 1) //hier 1 
		{
			return (len);
		}
		if (s[len + start] == '"')
		{
			while (s[len + start] != '\0' && s[len + start + 1] != '"')
				len++;
		}
		if (s[len + start] == 39)
		{
			while (s[len + start] != '\0' && s[len + start] != 39)
				len++;
		}
		if (s[len + start] != 0)
			len++;
	}
	return (len);
}

static int	getslen(char const *s, int start, int *equal_no)
{
	int			len;

	len = 0;
	if (s[len + start] == '<' || s[len + start] == '>')
		return (1 + handle_rds(s, start));
	else if (s[len + start] == '|')//|| s[len + start] == '=')
	{
		*equal_no = 1;
		return (1);
	}	
	else if (s[len + start] == '=')
	{
		//printf("hallo\n");
		if (s[len + start + 1] != '\0' && s[len + 
			start + 1] != ' ' && !is_op(s[len + start + 1]) && len + start != 0/*&& s[len + start - 1] != '\0'*/ && s[len + 
			start - 1] != ' ' && !is_op(s[len + start - 1]) && *equal_no == 1)
		{
			//printf("%c is =\n", s[len + start]);
			*equal_no = 2;
			return (1);
		}
	}
	//printf("%c has %d\n", s[len + start], *equal_no);
	len = getslen2(s, start, len, *equal_no);
	return (len);
}

static char	*ft_createsubstr(char const *s, int start, int *j, int *equal_no)
{
	int		len;
	int		i;
	//int		j;
	char	*str;

	len = getslen(s, start, equal_no);
	i = 0;
	//j = 0;
	if (len == 0)
		return ("");
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while ((*j - start) < len)
	{
		if (s[*j] != '"' && s[*j] != 39)
		{
			str[i] = s[*j];
			i++;
		}
		*j += 1;
	}
	str[i] = '\0';
	return (str);
}

/*static char	*ft_createsubstr(char const *s, int start)
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
}*/

static void	fix_order(char ***strarr)
{
	int		i;
	char	*tmp;

	i = 0;
	while (strarr[0][i] != NULL)
	{
		if (strarr[0][i][0] == '=' && strarr[0][i][1] == 0)
		{
			tmp = strarr[0][i];
			strarr[0][i] = strarr[0][i - 1];
			strarr[0][i - 1] = tmp;
		}
		i++;
	}
	i = 0;
	//while (strarr[0][i] != NULL)
	//{
		//printf("%s\n", strarr[0][i]);
	//	i++;
	//}
}

int	cmd_split(char const *s, char ***strarr, int *equal_no)
{
	int		i;
	int		j;
	int		ccount;
	int		start;
	//char	**strarr;

	ccount = ft_ccount(s);
	//strarr = *strarr;
	*strarr = malloc(sizeof(char *) * (ccount + 1));
	if (!strarr)
	{
		free((char *)s);
		//return (NULL);
	}
	i = 0;
	j = 0;
	while (i < ccount)
	{
		while (s[j] == ' ')
			j++;
		start = j;
		//j += getslen(s, start);
		strarr[0][i] = ft_createsubstr(s, start, &j, equal_no);
		if (strarr[0][i] == NULL)
		{
			free_split(*strarr, i, (char *)s);
			//return (NULL);
		}
		i++;
	}
	strarr[0][i] = NULL;
	fix_order(strarr);
	//return (strarr);
	return (ccount);
}

/*
int	main(void)
{
	int i = 0;
	char	**strarr = ft_split("sort =input.txt | uniq>>laaa");
	while (i < 7)
	{
		printf("%s\n", strarr[i]);
		i++;
	}
	free(strarr);
	return (0);
}*/


static char	*ft_createsubstr(char const *s, int start, int *j)
{
	int		len;
	int		i;
	//int		j;
	char	*str;

	len = getslen(s, start);
	i = 0;
	//j = 0;
	if (len == 0)
		return ("");
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while ((*j - start) < len)
	{
		if (s[*j] != '"' && s[*j] != 39)
		{
			str[i] = s[*j];
			i++;
		}
		*j += 1;
	}
	str[i] = '\0';
	return (str);
}