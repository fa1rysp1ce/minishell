

#include "minishell_exec.h"

void    print_list(t_token **head);

void    init_tokens(t_token **head)
{
    t_token *new_node;

    //CMD
    new_node = NULL;
    new_node = add_node(head);
    // new_node->is_append = 1;
    new_node->type = CMD;
    new_node->args = malloc(sizeof(char *) * 2);
    new_node->args[0] = ft_strdup("cat");
    // new_node->args[1] = ft_strdup("h=666");
    // new_node->args[2] = ft_strdup("l");
    new_node->args [1] = NULL;


    //REDIRECT
    new_node = NULL;
    new_node = add_node(head);
    new_node->type = HDOC;
    new_node->args = malloc(sizeof(char *) * 2);
    new_node->args[0] = ft_strdup("dimi0");
    new_node->args [1] = NULL;

    //REDIRECT
    new_node = NULL;
    new_node = add_node(head);
    new_node->type = HDOC;
    new_node->args = malloc(sizeof(char *) * 2);
    new_node->args[0] = ft_strdup("dimi");
    new_node->args [1] = NULL;
/*
    //REDIRECT
    new_node = NULL;
    new_node = add_node(head);
    new_node->type = IN;
    new_node->args = malloc(sizeof(char *) * 2);
    new_node->args[0] = ft_strdup("test.txt");
    new_node->args [1] = NULL;


    //PIPE
    new_node = NULL;
    new_node = add_node(head);
    new_node->type = PIPE;


    //CMD
    new_node = NULL;
    new_node = add_node(head);
    new_node->type = CMD;
    new_node->args = malloc(sizeof(char *) * 3);
    new_node->args[0] = ft_strdup("grep");
    new_node->args[1] = ft_strdup("t");
    new_node->args [2] = NULL;






// 2 cmds 
    new_node = add_node(head);
    new_node->type = PIPE;

    new_node = NULL;

    new_node = add_node(head);
    new_node->type = CMD;
    new_node->args = malloc(sizeof(char *) * 3);
    new_node->args[0] = ft_strdup("grep");
    new_node->args[1] = ft_strdup("");
    new_node->args [1] = NULL;
*/
    print_list(head);



}
void    print_list(t_token **head)
{
    t_token *node;
    int i;

    if (!*head || !head)
        return ;
    node = *head;
    while (node)
    {
        printf("####\n");
        switch (node->type)
        {
            case 0:
                printf("type: CMD\n");
                break ;
            case 1:
                printf("type: PIPE\n");
                break ;
            case 2:
                printf("type: IN\n");
                break ;
            case 3:
                printf("type: OUT\n");
                break ;
            case 4:
                printf("type: OUT_APP\n");
                break ;
            case 5:
                printf("type: HDOC\n");
                break ;
        }
        // printf("type: %d\n", node->type);
        if (node->args)
        {
            i = 0;
            while (node->args[i])
            {
                printf("args[%d]: %s\n", i, node->args[i]);
                i++;
            }
        }
        node = node->next;
    }
    printf("####\n");
}


t_token	*add_node(t_token **node)
{
	t_token	*new_node;
	t_token *curr;

	new_node = malloc(sizeof(t_token));
	// if (!new_node)
		//exit handle
	new_node->next = NULL;
	new_node->args = NULL;
	new_node->type = 7;
	
	if (*node == NULL)
	{
	//	new_node->prev = NULL;
		*node = new_node;
		return (*node);
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


void    clean_tokens(t_token **head_token)
{
    t_token *token;
    t_token *tmp;

    tmp = NULL;
    token = *head_token;
    while (token != NULL)
    {
        // printf("clean: node type: %d\n", token->type);
        if (token->args != NULL)
            free_2d_charr(token->args);
        tmp = token;
        token = token->next;
        free(tmp);
    }
    head_token = NULL;
}