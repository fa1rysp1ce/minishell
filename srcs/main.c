/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:46:28 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/13 14:10:21 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_history(char *line);
void		print_list_inbar(t_token **head);

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	t_token	*ls_ptr;
	char	*line;

	(void)ac;
	(void)av;
	ls_ptr = NULL;
	init_shell(&shell, env);
	while (1)
	{
		signal_interactive();
		line = readline(GREEN BOLD "minishell>" DEFAULT " ");
		if (line == NULL)
		{
			set_exit_status(EXIT_SUCCESS);
			break ;
		}
		set_history(line);
		if (parse(&ls_ptr, &line, &shell) != 0)
			continue ;
		signal_noninteractive();
		// print_list_inbar(&ls_ptr);
		execution_junction(&shell, &ls_ptr);
	}
	clean_shell(&shell);
	return (get_exit_status());
}

static void	set_history(char *line)
{
	add_history(line);
	rl_replace_line((const char *)line, 0);
	rl_redisplay();
}

void	print_list_inbar(t_token **head)
{
	t_token	*node;
	int		i;

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
