#include "safe_malloc.h"

/*int	main(void)
{
	t_node *list = NULL;
	int j = 789;
	int *jj;
	int k = 666;
	int *kk;

	printf("1\n");
	jj = malloc(sizeof(int *));
	*jj = j;
	safe_malloc(&list, jj, PTR);
	safe_malloc(&list, &j, FILE);
	kk = malloc(sizeof(int *));
	*kk = k;
	safe_malloc(&list, kk, PTR);
	safe_malloc(&list, &k, FILE);
	printf("2\n");
	safe_m_print(&list);
	safe_free(&list);
	return (0);
}*/

void	*safe_malloc(t_node **node, void *ptr, int file)
{
	t_node	*new_node;
	t_node *curr;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(1);
		//exit handle
	new_node->ptr = ptr;
	new_node->file = file;
	new_node->next = NULL;
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

void	safe_free(t_node **list)
{
	t_node *curr;
	t_node *prev;
	//int		fd;

	curr = *list;
	while (curr != NULL)
	{
		//printf("2 node nr.%d:\n\n", i);
		if (curr->file == PTR)
			free(curr->ptr);
		else if (curr->file == FILE)
		{
			//(int *)curr->ptr;
			//fd = *(curr->ptr)
			//close(*(curr->ptr));
			close(*(int *)(curr->ptr));
		}
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	*list = NULL;
}

void	safe_m_print(t_node **list)
{
	t_node *curr;
	//t_node *prev;
	//int		fd;

	curr = *list;
	while (curr != NULL)
	{
		//printf("2 node nr.%d:\n\n", i);
		if (curr->file == PTR)
			printf("%p\n", curr->ptr);
		else if (curr->file == FILE)
		{
			printf("%d\n", *(int *)(curr->ptr));
		}
		//prev = curr;
		curr = curr->next;
		//free(prev);
	}
	//*list = NULL;
}
