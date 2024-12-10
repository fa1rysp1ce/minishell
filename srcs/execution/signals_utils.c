/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:21:23 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/10 16:23:26 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int     g_status;

//ctrl+\ while in cmd child, for example in case of an open command waiting for input
void    handle_sigquit(int sig)
{
    (void)sig;
    ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
}

//ctrl+c while in cmd child
void    handle_sigint_child(int sig)
{
    (void)sig;
    write(1, "\n", 1);
}

//ctrl+c in parent must update global and prompt new line
void    handle_sigint(int sig)
{
    (void)sig;
    set_exit_status(SIG_TERM);
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void    handle_sigint_hdoc(int sig)
{
    char    *args;
    
    (void)sig;
    args = NULL;
    write(1, "\n", 1);
    execve("/bin/false", &args, NULL);
}
