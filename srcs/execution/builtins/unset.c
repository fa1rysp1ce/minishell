/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:26:25 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/12 16:43:27 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_realloc(t_shell *shell, int i);

int	unset(t_shell *shell, t_token *token)
{
	int	i;
	int	j;

	j = 0;
	while (token->args[++j] != NULL)
	{
		i = -1;
		while (shell->envc[++i] != NULL)
		{
			if (ft_strncmp(shell->envc[i], token->args[j],
					ft_strlen(token->args[j])) == 0)
				break ;
		}
		if (shell->envc[i] != NULL)
		{
			free(shell->envc[i]);
			while (shell->envc[i + 1] != NULL)
			{
				shell->envc[i] = shell->envc[i + 1];
				i++;
			}
			unset_realloc(shell, i);
		}
	}
	return (EXIT_SUCCESS);
}

static void	unset_realloc(t_shell *shell, int i)
{
	shell->envc = (char **)realloc(shell->envc, ((i + 1) * sizeof(char *)));
	shell->envc[i] = NULL;
}
