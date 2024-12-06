/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:51:50 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/06 13:56:57 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     g_status;

void	set_exit_status(int nbr)
{
    g_status = nbr;
}

int		get_exit_status(void)
{
    return (g_status);
}
