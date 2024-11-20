/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:26:09 by ilazar            #+#    #+#             */
/*   Updated: 2024/10/30 19:19:37 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static  int count_nodes_for_pipes(void) //stack of nodes
{
    //to do
    // if no pipes needed return 0
    return (1);
}


static int  **create_pipes(int *pipes_num) //create array only?
{
    int **fd;
    // int i;

    *pipes_num = count_nodes_for_pipes();
    if (*pipes_num == 0)
        return (NULL);
    fd = (int **) malloc(sizeof(int *) * (*pipes_num - 1));
    if (fd == NULL)
    {
        printf("malloc error");
        return (NULL);
    }
    // i = 0;
    // while (i < *pipes_num)
    // {
    //     fd[i] = (int *) malloc(sizeof(int) * 2);
    //     if (pipe(fd[i]) == -1)
    //     {
    //         //free cmd table jack
    //         close_pipes(fd, i);
    //         free_pipes(fd, i);
    //         perror("pipes");
    //         exit(2); //maybe not exit but back to main?
    //     }
    //     i++;
    // }
    return (fd);
}


void    init_execution(t_shell *shell)
{
    t_execute *exec;

    exec = shell->execute;
    exec->pipes_num = 0;
    exec->fd = create_pipes(&exec->pipes_num);
    
    exec->proc_num = exec->pipes_num + 1;
    exec->pid = create_processes(exec->proc_num);
    if (exec->pid == NULL)
    {
        //free table jack
        //close_pipes(exec->fd, exec->pipes_num); no need
        free_pipes(exec->fd, exec->pipes_num);
        perror("malloc");
        exit(2); 
    }
    // print_pipes(exec->fd, exec->pipes_num);
    print_procs(exec->pid, exec->proc_num);
}

int	*create_processes(int proc_num)
{
    int *pid;
    int i;

    if (proc_num == 0)
        return (NULL);
    pid = (int *) malloc(sizeof(int) * proc_num);
    if (pid == NULL)
        return (NULL);
    i = 0;
    while (i < proc_num)
    {
        pid[i] = -1;
        i++;
    }
    return (pid);
}
