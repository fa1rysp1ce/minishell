/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:42:07 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/13 13:15:23 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *str)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	error_msg(char *name, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	exit_malloc_err(t_shell *shell)
{
	clean_heredocs(shell->execute);
	clean_exec(shell);
	clean_tokens(shell);
	clean_shell(shell);
	exit(MALLOC_ERROR);
}

int	abort_exec(char *msg, t_shell *shell)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	clean_heredocs(shell->execute);
	clean_exec(shell);
	clean_tokens(shell);
	clean_shell(shell);
	exit (EXEC_ERROR);
}
