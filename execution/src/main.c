/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:33:26 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/20 13:56:11 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int main(int ac, char **av, char **env)
{
    t_shell shell;
    //char    *line;
    //fake nodes
    t_token *head_token;
  
    head_token = NULL;
    init_shell(&shell, env);
    // prof of env picture made
    // int	i = 0;
	// while (shell.envc[i] != NULL)
	// 	printf("%s$\n", shell.envc[i++]);
    
    

    // create_table(&token);
    
    init_tokens(&head_token);
    // shell.head_token = &head_token;
    
    // printf("*token made\n");
    
    execution_junction(&shell, &head_token);
    
    
    printf("\n##\n");
    printf("*last exit status: %d\n", shell.last_exit_status);
    
    // printf("\n\n\n\n");
    // print_2darray(shell.envc);
    
    // execution_junction(&shell, &head_token);
    
    clean_shell(&shell);
    
    //init_execution(&shell);
    //execute(&shell);
   
   
    // free_paths(&shell);
    
    (void)ac;
    (void)av;
    
    // while(1)
    // {
    //     line = readline(GREEN BOLD"minishell$>"DEFAULT" ");
    //     free(line);
    // }

    
    
    return (0);
}


