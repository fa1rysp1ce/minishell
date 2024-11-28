/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:54:08 by inbar             #+#    #+#             */
/*   Updated: 2024/11/28 13:10:13 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int fork_pipeline(t_shell *shell, int pipe_fd[2][2], int last_pipe, int new_pipe);
static void    set_pipes(int pipe_fd[2][2], int last_pipe, int new_pipe, int i);
static void    wait_pids(t_execute *exec, int *status);


//assumes first token is a cmd
void    pipeline(t_shell *shell)
{
    int     pipe_fd[2][2];
    int     last_pipe;
    int     new_pipe;
    

    shell->execute->pid = malloc(sizeof(pid_t) * shell->execute->cmds);
    if (shell->execute->pid == NULL)
        exit_malloc_err(shell);
    new_pipe = 1;
    last_pipe = 0;

    shell->last_exit_status = fork_pipeline(shell, pipe_fd, last_pipe, new_pipe);

    //print heredocs
    int i = 0;
	while (i < shell->execute->hdocs)
    {
        printf("heredoc[%d] read_end after pipe: %d\n", i, shell->execute->heredocs[i].read_end_open);
        i++;
    }
    
}

static void    wait_pids(t_execute *exec, int *status)
{
    int cmd_count;

    cmd_count = 0;
    while (cmd_count < exec->cmds)
        waitpid(exec->pid[cmd_count++], status, 0);
    free(exec->pid);
}

static int fork_pipeline(t_shell *shell, int pipe_fd[2][2], int last_pipe, int new_pipe)
{
    int status;
    int cmd_count;
    
    status = 0;
    cmd_count = 0;
    while (cmd_count < shell->execute->cmds)
    {
        if (cmd_count < shell->execute->cmds - 1 ) //if it's not the last cmd
            if (pipe(pipe_fd[new_pipe]) < 0)
                return (abort_exec("Error: pipe\n", shell));
        shell->execute->pid[cmd_count] = fork();
        if (shell->execute->pid[cmd_count] < 0)
            return (abort_exec("Error: fork\n", shell));
        if (shell->execute->pid[cmd_count] == 0)
            child_exec(shell, pipe_fd, last_pipe, cmd_count);
        if (cmd_count > 0 && shell->execute->cmds >= 1) //not 1st cmd and no single cmd
                close_pipes(pipe_fd, last_pipe);
        close_used_heredocs(shell); //set 0 to indicate what heredocs were used. hopefully not closing them too fast for the children
        // printf("pipe!\n");
        next_cmd_token(shell);
        swap_pipes(&last_pipe, &new_pipe);
        cmd_count++;
    }
    close_pipes(pipe_fd, new_pipe); // - ?
    wait_pids(shell->execute, &status);
    return (WEXITSTATUS(status));
}

/*
static int fork_pipeline(t_shell *shell, int pipe_fd[2][2], int last_pipe, int new_pipe)
{
    int status;
    int cmd_count;
    pid_t pid;
    
    status = 0;
    cmd_count = 0;
    while (cmd_count < shell->execute->cmds)
    {
        if (cmd_count < shell->execute->cmds - 1 ) //if it's not the last cmd
            if (pipe(pipe_fd[new_pipe]) < 0)
                return (abort_exec("Error: pipe\n", shell));
        pid = fork();
        if (pid < 0)
            return (abort_exec("Error: fork\n", shell));
        if (pid == 0)
            child_exec(shell, pipe_fd, last_pipe, cmd_count);
        if (cmd_count > 0 && shell->execute->cmds >= 1) //not 1st cmd and no single cmd
                close_pipes(pipe_fd, last_pipe);
        parent(shell, status, pid, &cmd_count);
        swap_pipes(&last_pipe, &new_pipe);
        cmd_count++;
    }
    return (EXIT_SUCCESS);
}
*/
void 	child_exec(t_shell *shell, int pipe_fd[2][2], int last_pipe, int cmd_count)
{
    char    **args;
    char    *cmd_path;
    int     status;
    
    status = 127;
    args = shell->token->args;
    cmd_path = NULL;
    // if (pipe_fd)
    set_pipes(pipe_fd, last_pipe, shell->execute->cmds, cmd_count);
    if (redirection(shell) == EXIT_SUCCESS)
    {
        if (is_builtin(args[0]))
            status = execute_builtin(shell);
        else   
            cmd_path = get_cmd_path(shell);
        if (cmd_path != NULL)
        {
            status = execve(cmd_path, args, shell->envc);
            free(cmd_path);
        }
    }
    restore_fds(shell);
    clean_exec(shell);
    clean_tokens(shell);
    clean_shell(shell);
    exit(status);
}

/* 
    if the next cmd in the pipe is the last and it's a builtin - 
    will execute it in the parent and end the pipe loop 
*/ 
// static void    parent(t_shell *shell, int status, pid_t pid, int *cmd_count) //maybe pid is always 0 ?
// {
//     waitpid(pid, &status, 0);
//     update_exit_status(shell, status);
//     next_cmd_token(shell);
    
//     //last command runs in parent if its a builtin - ??
//     (void) cmd_count;
    
//     // if (*cmd_count == shell->execute->cmds - 1) 
//     //     if (is_builtin(shell->token->args[0])) //last cmd and builtin - do in parent
//     //     {
//     //         single_builtin(shell);
//     //         *cmd_count = *cmd_count + 1;
//     //     }
// }

//do nothing if theres only one cmd
static void    set_pipes(int pipe_fd[2][2], int last_pipe, int cmds, int cmd_count)
{
    int new_pipe;

    new_pipe = 0;
    if (last_pipe == 0)
        new_pipe = 1;
    if (cmd_count > 0) //not first cmd, read from last pipe
    {
        dup2(pipe_fd[last_pipe][0], STDIN_FILENO);
        close_pipes(pipe_fd, last_pipe);
    }
    if (cmd_count < cmds - 1) //not last cmd. write to new pipe
    {
        dup2(pipe_fd[new_pipe][1], STDOUT_FILENO);
        close_pipes(pipe_fd, new_pipe);
    }
}
