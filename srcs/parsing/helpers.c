#include "minishell.h"

int skip_quoted(const char *s, int i)
{
	if (s[i] == '"')
	{
		i++;
		while (s[i] != '\0' && s[i] != '"')
			i++;
	}
	else if (s[i] == 39)
	{
		i++;
		while (s[i] != '\0' && s[i] != 39)
			i++;
	}
	return (i);
}