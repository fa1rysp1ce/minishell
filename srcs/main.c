/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:46:28 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/13 12:51:57 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_history(char *line);

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
