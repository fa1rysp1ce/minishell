/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:24:46 by inbar             #+#    #+#             */
/*   Updated: 2024/12/03 20:21:02 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_sigint(int sig)
{
    (void)sig;
    write(1, "^C\n", 3);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int     event_hook(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);  // Initialize the signal mask
    sa.sa_flags = 0;  // No special flags

    sigaction(SIGINT, &sa, NULL);

    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
    return (EXIT_SUCCESS);
    
}