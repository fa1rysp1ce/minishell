/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:00:53 by junruh            #+#    #+#             */
/*   Updated: 2024/12/12 18:13:41 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*add_node(t_token **node, char **strarr, int pos)
{
	t_token	*new_node;
	t_token	*curr;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		exit_fill_list(strarr, pos, node);
	new_node->type = -1;
	new_node->next = NULL;
	new_node->args = NULL;
	if (*node == NULL)
	{
		*node = new_node;
		return (0);
	}
	curr = *node;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = new_node;
	return (new_node);
}

t_token	*find_last(t_token **list)
{
	t_token	*curr;

	curr = *list;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	return (curr);
}

/*void	print_list(t_token **list)
{
	int	i;
	int j;
	t_token *curr;

	i = 1;
	curr = *list;
	while (curr != NULL)
	{
		printf("node nr.%d:\n\n", i);
		j = 0;
		while (curr->args != NULL && curr->args[j] != NULL)
		{
			printf("%s\n", curr->args[j]);
			j++;
		}
		printf("type: %d\n", curr->type);
		printf("\n");
		curr = curr->next;
		i++;
	}
}*/

void	free_list(t_token **list)
{
	int		j;
	t_token	*curr;
	t_token	*prev;

	curr = *list;
	while (curr != NULL)
	{
		j = 0;
		while (curr->args != NULL && curr->args[j] != NULL)
		{
			free(curr->args[j]);
			j++;
		}
		free(curr->args);
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	*list = NULL;
}
