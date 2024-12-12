/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junruh <junruh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:17:35 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/12 19:45:30 by junruh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_shell(t_shell *shell)
{
	if (shell->envc)
		free_2d_charr(shell->envc);
	if (shell->prev_dir)
		free(shell->prev_dir);
	rl_clear_history();
}

void	clean_tokens(t_shell *shell)
{
	free_list(shell->head_token);
	shell->head_token = NULL;
	shell->token = NULL;
}

void	clean_exec(t_shell *shell)
{
	if (shell->execute->org_fds)
		free(shell->execute->org_fds);
	shell->execute->org_fds = NULL;
	if (shell->execute->pid)
		free(shell->execute->pid);
	shell->execute->pid = NULL;
	clean_heredocs(shell->execute);
	if (shell->execute)
		free(shell->execute);
	shell->execute = NULL;
}

void	clean_heredocs(t_execute *exec)
{
	if (exec->heredocs)
		free(exec->heredocs);
	exec->heredocs = NULL;
}

void	free_2d_charr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}
