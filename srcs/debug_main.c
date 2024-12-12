/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:51:18 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/12 16:55:23 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// a main for debuging purposes
int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	t_token	*head_token;

	init_shell(&shell, env);
	head_token = NULL;
	(void)ac;
	(void)av;
	init_tokens(&head_token);
	print_list_inbar(&head_token);
	execution_junction(&shell, &head_token);
	clean_tokens(&shell);
	clean_shell(&shell);
	return (0);
}

/*
Extra addition to pipeline:
	if shopt -s lastpipe option is enabled:
	when the next cmd in the pipe is the last and it's a builtin -
	will execute it in the parent and end the pipe loop.
	to disable: shopt -u lastpipe

	can be placed before "next_cmd_token()" in pipeline function

static void	lastpipe_option(t_shell *shell, int status, pid_t pid,
		int *cmd_count)
{
	if (*cmd_count == shell->execute->cmds - 1)
		if (is_builtin(shell->token->args[0]))
			//last cmd and builtin- do in parent
		{
			single_builtin(shell);
			*cmd_count = *cmd_count + 1;
		}
}
*/