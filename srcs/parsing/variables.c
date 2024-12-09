#include "minishell.h"

void	check_vars(char **line, t_shell *shell)
{
	int	i;
	int j;

	i = 0;
	while (line[0][i] != 0)
	{
		j = 0;
		if (line[0][i] == 39)
		{
			i++;
			while (line[0][i] != 39 && line[0][i] != 0)
				i++;
			if (line[0][i] == 39)
        		i++;
		}
		if (line[0][i] == '$')
		{
			j = i + 1;
			while (line[0][j] != 0 && line[0][j] != ' ' && line[0][j] != '"' && line[0][j] != '$')
			{
				j++;
			}
			if (i + 1 < j)
				handle_vars(line, i, j - i, shell);
			//i = j;
		}
		if (line[0][i] != 0)
			i++;
	}
}

char *find_var(char *str, t_shell *shell)
{
	char 	*res;

	if (!ft_strcmp(str, "?"))
		res = ft_itoa(get_exit_status());
	else
	{
		res = ft_strdup(expand_arg(shell, str));
	}
	if (res == NULL || res[0] == 0)
	{
		res = ft_strdup("");
		if (!res)
			return (NULL);
	}
	return (res);
}

void	handle_vars(char **line, int i, int len, t_shell *shell)
{
	int	k;
	char	*str;
	char	*newstr;
	char	*tmp;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		exit_variables(*line);
	k = 0;
	while (k < len - 1)
	{
		str[k] = line[0][i + k + 1];
		k++;
	}
	str[k] = 0;
	//printf("%s\n", str);
	newstr = find_var(str, shell);
	free(str);
	if (newstr == NULL)
		exit_variables(*line);
	//printf("%s\n", newstr);
	tmp = replace_var(line, i, len, newstr);
	if (tmp == NULL)
		exit_variables(*line);
	free(*line);
	*line = tmp;
}


char	*replace_var(char **line, int start, int len, char *substr)
{
	int i;
	int	j;
	char	*newline;

	//printf("Line length: %zu, Substring length: %zu, len: %d\n", ft_strlen(*line), ft_strlen(substr), len);
	newline = malloc(sizeof(char) * (ft_strlen(*line) + ft_strlen(substr) - len + 1));
	if (!newline)
		return (NULL); 
	i = 0;
	while (i < start)
	{
		newline[i] = line[0][i];
		i++;
	}
	j = i;
	while (substr[i - j] != 0)
	{
		newline[i] = substr[i - j];
		i++;
	}
	j = start + len;
	while (line[0][j] != 0)
		newline[i++] = line[0][j++];
	newline[i] = 0;
	free(substr);
	return (newline);
}
