/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:42:07 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/19 20:11:05 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

//void    free_pipes(int **fd, int pipes_num)
// void    free_processes(int *pid, int proc_num)

void    exit_error(char *str)
{
    printf("Error: %s\n", str);
    exit(1);
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
    clean_shell(shell); //shell init and token
    exit(MALLOC_ERROR);
}

int abort_exec(char *msg, t_shell *shell)
{
    ft_putstr_fd(msg, STDERR_FILENO);
    clean_exec(shell);
    if (shell->token) //change to proper cleanup token
        free_2d_charr(shell->token->args);
    shell->token = NULL;
    return (EXEC_ERROR);
}
