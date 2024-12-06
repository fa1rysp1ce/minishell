/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:24:46 by inbar             #+#    #+#             */
/*   Updated: 2024/12/06 15:31:36 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int     g_status;

static void    handle_sigint(int sig);
static void    handle_sigint_hdoc(int sig);
static void    handle_sigquit(int sig);
static void    handle_sigint_child(int sig);

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
//in case of an open command (for example: wc)
void    signal_child_proc(void)
{
    signal(SIGINT, handle_sigint_child);
    signal(SIGQUIT, handle_sigquit);
}

void    signal_heredoc(void)
{
    signal(SIGINT, handle_sigint_hdoc);
    signal(SIGQUIT, SIG_IGN);
}
//ctrl+\ while in cmd child, for example in case of an open command waiting for input
static void    handle_sigquit(int sig)
{
    (void)sig;
    ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
    // set_exit_status(SIG_QUIT);
}

//ctrl+c while in cmd child
static void    handle_sigint_child(int sig)
{
    (void)sig;
    // set_exit_status(SIG_TERM);
    write(1, "\n", 1);
    // rl_replace_line("", 0);
    // rl_on_new_line();
    // rl_redisplay();
}

//ctrl+c in parent must update global and prompt new line
static void    handle_sigint(int sig)
{
    (void)sig;
    set_exit_status(SIG_TERM);
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

static void    handle_sigint_hdoc(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    char *args = {NULL};
    execve("/bin/false", &args, NULL);
}