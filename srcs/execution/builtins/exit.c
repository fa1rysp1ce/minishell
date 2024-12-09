/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:27:20 by ilazar            #+#    #+#             */
/*   Updated: 2024/12/02 15:04:40 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int     is_numeric_arg(char *str)
{
    int i;     
    
    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] != '\0')
    {
        if (ft_isdigit(str[i]) == 0)
        {
            ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
            ft_putstr_fd(str, STDERR_FILENO);
            ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
            return (EXIT_FAILURE);
        }
        i++;
    }
    return(EXIT_SUCCESS);
}

int   exit_cmd(t_shell *shell)
{
    int     status;

    status = EXIT_SUCCESS;
    if (shell->token->args[1] != NULL)
    {
        if (is_numeric_arg(shell->token->args[1]) == EXIT_SUCCESS)
        {
            if (shell->token->args[2] != NULL)
            {
                error_msg("exit", "too many arguments");
                return (EXIT_FAILURE);
            }
            status = ft_atoi(shell->token->args[1]);
        }
        else
            status = BUILTIN_MISUSE;
    }
    clean_exec(shell);
    clean_tokens(shell);
    clean_shell(shell);
    exit(status);
}
