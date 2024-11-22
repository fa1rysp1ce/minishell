#include "minishell.h"


void	*add_node(t_token **node)
{
	t_token	*new_node;
	t_token *curr;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		exit(1);
		//exit handle
	new_node->type = -1;
	new_node->next = NULL;
	new_node->args = NULL;
	//new_node->input = NULL;
	//new_node->is_append = 0;
	//new_node->output = NULL;
	//new_node->heredoc = 0;
	if (*node == NULL)
	{
	//	new_node->prev = NULL;
		*node = new_node;
		return (0);
	}
	curr = *node;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	//new_node->prev = curr;
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

void	print_list(t_token **list)
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
		//printf("mimimi\n");
		//printf("input file:%s\n", curr->input);
		//printf("is heredoc:%d\n", curr->heredoc);
		//printf("output file:%s\n", curr->output);
		//printf("is append:%d\n", curr->is_append);
		printf("\n");
		curr = curr->next;
		i++;
	}
}

void	free_list(t_token **list)
{
	//int	i;
	int j;
	t_token *curr;
	t_token *prev;

	//i = 1;
	curr = *list;
	while (curr != NULL)
	{
		//printf("2 node nr.%d:\n\n", i);
		j = 0;
		while (curr->args != NULL && curr->args[j] != NULL)
		{
			//printf("2 %s\n", curr->args[j]);
			free(curr->args[j]);
			j++;
		}
		free(curr->args);
		//printf("2 type: %d\n", curr->type);
		//printf("2 input file:%s\n", curr->input);
		//if (curr->input != NULL)
		//	free(curr->input);
		//printf("2 is heredoc:%d\n", curr->heredoc);
		//printf("2 output file:%s\n", curr->output);
		//if (curr->output != NULL)
		//	free(curr->output);
		//printf("2 is append:%d\n", curr->is_append);
		//printf("\n\n");
		prev = curr;
		curr = curr->next;
		free(prev);
		//i++;
	}
	*list = NULL;
}
