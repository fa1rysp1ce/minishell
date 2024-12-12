/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:49:48 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/12 13:53:26 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_tokens(t_token **head)
{
    t_token *new_node;

    //CMD
    new_node = NULL;
    new_node = add_node_inbar(head);
    // new_node->is_append = 1;
    new_node->type = CMD;
    new_node->args = malloc(sizeof(char *) * 3);
    new_node->args[0] = ft_strdup("echo");
    new_node->args[1] = ft_strdup("-n hello world");
    // new_node->args[2] = ft_strdup("l");
    new_node->args [2] = NULL;


/*
    //REDIRECT
    new_node = NULL;
    new_node = add_node_inbar(head);
    // new_node->type = HDOC;
    new_node->type = IN;
    new_node->args = malloc(sizeof(char *) * 2);
    new_node->args[0] = ft_strdup("f1.txt");
    new_node->args [1] = NULL;

    //REDIRECT
    new_node = NULL;
    new_node = add_node_inbar(head);
    new_node->type = HDOC;
    new_node->args = malloc(sizeof(char *) * 2);
    new_node->args[0] = ft_strdup("1");
    new_node->args [1] = NULL;

    //REDIRECT
    new_node = NULL;
    new_node = add_node_inbar(head);
    new_node->type = HDOC;
    new_node->args = malloc(sizeof(char *) * 2);
    new_node->args[0] = ft_strdup("1");
    new_node->args [1] = NULL;



    //PIPE
    new_node = NULL;
    new_node = add_node_inbar(head);
    new_node->type = PIPE;

    //CMD
    new_node = NULL;
    new_node = add_node_inbar(head);
    new_node->type = CMD;
    new_node->args = malloc(sizeof(char *) * 3);
    new_node->args[0] = ft_strdup("catx");
    // new_node->args[1] = ft_strdup("a");
    new_node->args [1] = NULL;


    //REDIRECT
    new_node = NULL;
    new_node = add_node_inbar(head);
    new_node->type = HDOC;
    // new_node->type = IN;
    new_node->args = malloc(sizeof(char *) * 2);
    new_node->args[0] = ft_strdup("2");
    new_node->args [1] = NULL;


    //REDIRECT
    new_node = NULL;
    new_node = add_node_inbar(head);
    new_node->type = HDOC;
    new_node->args = malloc(sizeof(char *) * 2);
    new_node->args[0] = ft_strdup("2");
    new_node->args [1] = NULL;

*/

/*
    //PIPE
    new_node = NULL;
    new_node = add_node_inbar(head);
    new_node->type = PIPE;

    //CMD
    new_node = NULL;
    new_node = add_node_inbar(head);
    new_node->type = CMD;
    new_node->args = malloc(sizeof(char *) * 2);
    new_node->args[0] = ft_strdup("catt");
    // new_node->args[1] = ft_strdup("x");
    new_node->args [1] = NULL;


    //REDIRECT
    new_node = NULL;
    new_node = add_node_inbar(head);
    new_node->type = HDOC;
    new_node->args = malloc(sizeof(char *) * 2);
    new_node->args[0] = ft_strdup("2");
    new_node->args [1] = NULL;

    new_node = add_node_inbar(head);
    new_node->type = PIPE;

    new_node = NULL;

    new_node = add_node_inbar(head);
    new_node->type = CMD;
    new_node->args = malloc(sizeof(char *) * 3);
    new_node->args[0] = ft_strdup("grep");
    new_node->args[1] = ft_strdup("");
    new_node->args [1] = NULL;
*/
    print_list_inbar(head);
}

void    print_list_inbar(t_token **head)
{
    t_token *node;
    int i;

    if (!*head || !head)
        return ;
    node = *head;
    while (node != NULL)
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
                printf("type: HDOC\n");
                break ;
            case 4:
                printf("type: OUT\n");
                break ;
            case 5:
                printf("type: OUT_APP\n");
                break ;
        }
        if (node->args != NULL)
        {
            i = 0;
            while (node->args[i] != NULL)
            {
                printf("args[%d]: %s\n", i, node->args[i]);
                i++;
            }
            if (node->args[i] == NULL)
                printf("args[%d]: NULL\n", i);
        }
        node = node->next;
    }
    printf("####\n");
}


t_token	*add_node_inbar(t_token **node)
{
	t_token	*new_node;
	t_token *curr;

	new_node = malloc(sizeof(t_token));
	new_node->next = NULL;
	new_node->args = NULL;
	new_node->type = 7;
	if (*node == NULL)
	{
		*node = new_node;
		return (*node);
	}
	curr = *node;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = new_node;
    return (new_node);
}


void    clean_tokens_inbar(t_token **head_token)
{
    t_token *token;
    t_token *tmp;

    tmp = NULL;
    token = *head_token;
    while (token != NULL)
    {
        if (token->args != NULL)
            free_2d_charr(token->args);
        tmp = token;
        token = token->next;
        free(tmp);
    }
    head_token = NULL;
}
