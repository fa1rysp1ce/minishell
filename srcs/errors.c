/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:42:07 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/11 18:06:46 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void    free_pipes(int **fd, int pipes_num)
// void    free_processes(int *pid, int proc_num)

void    exit_error(char *str)
{
    ft_putstr_fd("Error: ", STDERR_FILENO);
    ft_putstr_fd(str, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    exit(EXIT_FAILURE);
}

void    error_msg(char *name, char *msg)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(name, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd(msg, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}

//envc execute token path?
int    exit_malloc_err(t_shell *shell)
{
    clean_heredocs(shell->execute);
    clean_exec(shell);
    clean_tokens(shell);
    clean_shell(shell); //shell init and token
    exit(MALLOC_ERROR);
}

int abort_exec(char *msg, t_shell *shell)
{
    ft_putstr_fd(msg, STDERR_FILENO);
    clean_exec(shell);
    clean_tokens(shell);
    return (EXEC_ERROR);
}

//bash: warning: here-document delimited by end-of-file (wanted `4')
void    heredoc_eof_warning(char *delimiter)
{
    ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
    ft_putstr_fd("here-document delimited by end-of-file (wanted `", STDERR_FILENO);
    ft_putstr_fd(delimiter, STDERR_FILENO);
    ft_putstr_fd("')\n", STDERR_FILENO);
}   