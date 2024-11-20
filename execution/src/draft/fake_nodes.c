/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inbar <inbar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:31:45 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/12 20:49:59 by inbar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

/*typedef struct s_token
{
    char **args;
	int type;
    char *input;      // Name of input file for <
    char *output;     // Name of output file for > or >>
    int is_append; 
    struct s_token *next;
} t_token;*/

void make_arg(char *str, t_token *token, int x)
{
    int i;

    i = 0;
    if (str == NULL)
    {
        token->args = NULL;
        return ;
    }
    while (str[i] != '\0')
        i++;
    token->args[x] = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (str[i] != '\0')
    {
        token->args[x][i] = str[i];
        i++;
    }
    token->args[x][i] = '\0';
}

t_token   *create_cmd_node(char *demo_args[], int num_of_args)
{
    t_token *token;

    printf("enter create node\n");
    token = malloc(sizeof(token));


    int x = 0;
    token->is_append = 0; //for some crazy crazy reason is_append only works when located here
    //otherwise sigfault
    
    token->args = malloc(sizeof(char *) * (num_of_args + 2));
    while (x < num_of_args)
    {
        make_arg(demo_args[x], token, x);
        // printf("argsx: %s\n", token->args[x]);
        x++;
    }
    token->args[num_of_args] = NULL;

    token->type = CMD;

    token->input = NULL;
    token->output = NULL;
    // token->input = "test01.txt";
    // token->output = "test.txt";
    
    token->next = NULL;

    return (token);
}
void    add_last(t_token **token, t_token *node)
{
    t_token     *tmp;

    printf("enter add node\n");
    tmp = *token;
    if (*token == NULL)
    {
        *token = node;
        return ;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = node;
}

void    create_table(t_token **token)
{
    t_token *node;

    char *demo_args[] = {"echxxxo", "ssss", "test00.txt", "test00.txt", NULL};
    int num_of_args = 1;
    
    node = create_cmd_node(demo_args, num_of_args);
    printf("table: %s\n", node->args[0]);
    add_last(token, node);
}
/*
{"ls", "-l", NULL};

execve(args[0], )
*/