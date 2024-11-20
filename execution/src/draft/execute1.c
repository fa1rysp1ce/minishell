/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:40:55 by ilazar            #+#    #+#             */
/*   Updated: 2024/10/30 19:26:52 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// void    close_irrelevant_pipes(t_execute *exec, int proc_i)
// {
//     int i;
    
//     i = 0;
//     while (i < exec->pipes_num)
//     {

//         if (proc_i == 0 && i == 0)//first child
//         {
//             printf("first child i:%d\n", i);
//             printf("close [%d][0]\n", i);
//             close(exec->fd[i][0]);
//         }
//         else if (proc_i == exec->proc_num - 1 && i == proc_i - 1) //last child
//         {
//             printf("last child i:%d\n", i);
//             printf("close [%d][1]\n", i);
//             close(exec->fd[i][1]);
//         }
//         else
//         {
//             printf("mid child i:%d\n", i);
//             printf("close [%d][1]\n", i);
//             close(exec->fd[i][1]);
//         }
//         i++;
//     }
// }

/*
typedef struct s_token
{
	char	**args; {"ls", "-l", null}
	int		type; //cmd
	void	*next;
} t_token;
*/

void    set_pipes(t_execute *exec, int proc_indx)
{
    int input;
    int output;

    input = STDIN_FILENO;
    output = STDOUT_FILENO;
    (void)proc_indx;
    (void)exec;
}


void    child_proc(t_shell *shell, int proc_indx) //also ct node
{
    t_execute *exec;

    exec = shell->execute;
    printf("### child proc:     %d proc_i: %d\n", getpid(), proc_indx);
    
		int outfile = open("test00.txt", O_CREAT | O_WRONLY | O_TRUNC);
		if (outfile == -1)
			exit(3);
		dup2(exec->fd[proc_indx][0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		//close(fd[0]);
		//close(fd[1]);

    printf("fd: %d\n",exec->fd[proc_indx][0]);



    //close_irrelevant_pipes(exec, proc_indx); ??
    //set_pipes(exec, proc_indx);
    
    //redirections: in out  
    //std or file
    
    
    
    
    
    printf("### end child proc: %d\n", getpid());
    kill(getpid(), SIGTERM);
}

void    execute(t_shell *shell)
{
    t_execute exec;
    pid_t     pid;
    int       pid_count;
    
    shell->execute = &exec;
    init_execution(shell);
    pid_count = 0;
    printf("pipes num: %d proc num: %d\n", exec.pipes_num, exec.proc_num);
    while (pid_count < exec.proc_num)
    {
        if (pid_count < exec.proc_num - 1) //create pipes
        {
            if (pipe(exec.fd[pid_count]))
                exit(3);//TO DO
        }
        pid = fork();
        if (pid < 0)
        {
            printf("fork error %d\n", getpid());
            clean_all(shell);
            exit(3);
        }
        if (pid == 0) //child
            child_proc(shell, pid_count); //pass also the right cmd-node
        else
        {
            //if i won't kill the child before
            //he's gonna fork the next one
            waitpid(pid, NULL, 0);
            printf("parent waited %d\n", getpid());
        }
        pid_count++;
    }
    
    printf("parent end of loop %d\n", getpid());
    
   free_processes(exec.pid, exec.proc_num);
   free_pipes(exec.fd, exec.pipes_num);
}

/*
if type == cmd / redirection / pipe


*/