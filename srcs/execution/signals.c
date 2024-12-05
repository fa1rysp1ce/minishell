/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:24:46 by inbar             #+#    #+#             */
/*   Updated: 2024/12/05 18:01:04 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int      g_status;

static void    handle_sigint(int sig);
static void    handle_sigint2(int sig);

void    signal_interactive(void)
{
    
    signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void    signal_noninteractive(void)
{
    signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
//todo
void    signal_child_proc(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_DFL);
}
//todo
void    signal_heredoc(void)
{
    signal(SIGINT, handle_sigint2);
    // signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
}

static void    handle_sigint(int sig)
{
    (void)sig;
    g_status = 130;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

static void    handle_sigint2(int sig)
{
    (void)sig;
    g_status = 130;
    write(1, "\n", 1);
    // rl_replace_line("", 0);
    // rl_on_new_line();
    // rl_redisplay();
    char *args = {NULL};
    execve("/bin/false", &args, NULL);

}