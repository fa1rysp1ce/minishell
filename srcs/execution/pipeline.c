/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:54:08 by inbar             #+#    #+#             */
/*   Updated: 2024/12/11 14:16:59 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int fork_pipeline(t_shell *shell, int pipe_fd[2][2], int last_pipe, int new_pipe);
static void    set_pipes(int pipe_fd[2][2], int last_pipe, int new_pipe, int i);
static void    wait_pids(t_execute *exec, int *status);


void    pipeline(t_shell *shell)
{
    int     pipe_fd[2][2];
    int     last_pipe;
    int     new_pipe;
    int     status;
    

    shell->execute->pid = malloc(sizeof(pid_t) * shell->execute->cmds);
    if (shell->execute->pid == NULL)
        exit_malloc_err(shell);
    new_pipe = 1;
    last_pipe = 0;

    signal_child_proc();
    status = fork_pipeline(shell, pipe_fd, last_pipe, new_pipe);
    signal_noninteractive();
    set_exit_status(status);
    
    
    //print heredocs
    // int i = 0;
	// while (i < shell->execute->hdocs)
    // {
    //     printf("heredoc[%d] read_end after pipe: %d\n", i, shell->execute->heredocs[i].read_end_open);
    //     i++;
    // }
    
    free(shell->execute->pid);
}

static void    wait_pids(t_execute *exec, int *status)
{
    int cmd_count;

    cmd_count = 0;
    while (cmd_count < exec->cmds)
        waitpid(exec->pid[cmd_count++], status, 0);
    if (WIFSIGNALED(*status))
    {
        if (WTERMSIG(*status) == SIGQUIT)
            *status = SIG_QUIT;
        else
            *status = SIG_TERM;
    }
    else if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status);
}

/* open pipes - unless it's the last cmd
close pipes - unless its the 1st cmd or a single cmd */
static int fork_pipeline(t_shell *shell, int pipe_fd[2][2], int last_pipe, int new_pipe)
{
    int status;
    int cmd_count;
    
    status = 0;
    cmd_count = 0;
    while (cmd_count < shell->execute->cmds)
    {
        if (cmd_count < shell->execute->cmds - 1 ) 
            if (pipe(pipe_fd[new_pipe]) < 0)
                return (abort_exec("Error: pipe\n", shell));
        shell->execute->pid[cmd_count] = fork();
        if (shell->execute->pid[cmd_count] < 0)
            return (abort_exec("Error: fork\n", shell));
        if (shell->execute->pid[cmd_count] == 0)
            child_exec(shell, pipe_fd, last_pipe, cmd_count);
        if (cmd_count > 0 && shell->execute->cmds > 1)
                close_pipes(pipe_fd, last_pipe);
        close_used_heredocs(shell);
        next_cmd_token(shell);
        swap_pipes(&last_pipe, &new_pipe);
        cmd_count++;
    }
    wait_pids(shell->execute, &status);
    return (status);
}

void 	child_exec(t_shell *shell, int pipe_fd[2][2], int last_pipe, int cmd_count)
{
    char    **args;
    char    *cmd_path;
    int     status;
    
    status = NO_CMD;
    args = shell->token->args;
    cmd_path = NULL;
    set_pipes(pipe_fd, last_pipe, shell->execute->cmds, cmd_count);
    if (redirection(shell, &status) == EXIT_SUCCESS)
    {
        if (is_builtin(args[0]))
            status = execute_builtin(shell);
        else
            cmd_path = get_cmd_path(shell, &status);
        if (cmd_path != NULL)
        {
            execve(cmd_path, args, shell->envc);
            free(cmd_path);
        }
    }
    child_exec_fail(shell);
    exit(status);
}

/* set the pipes. do nothing if theres only one cmd
read from last pipe unless its the first cmd
write to new pipe unless its the last cmd */
static void    set_pipes(int pipe_fd[2][2], int last_pipe, int cmds, int cmd_count)
{
    int new_pipe;

    new_pipe = 0;
    if (last_pipe == 0)
        new_pipe = 1;
    if (cmd_count > 0)
    {
        dup2(pipe_fd[last_pipe][READ_END], STDIN_FILENO);
        close_pipes(pipe_fd, last_pipe);
    }
    if (cmd_count < cmds - 1)
    {
        dup2(pipe_fd[new_pipe][WRITE_END], STDOUT_FILENO);
        close_pipes(pipe_fd, new_pipe);
    }
}

/* 
    if shopt -s lastpipe option is enabled:
    when the next cmd in the pipe is the last and it's a builtin - 
    will execute it in the parent and end the pipe loop.
    to disable: shopt -u lastpipe
    
    can be placed before "next_cmd_token()" in pipeline function
    
static void    lastpipe_optin(t_shell *shell, int status, pid_t pid, int *cmd_count) //maybe pid is always 0 ?
{
    if (*cmd_count == shell->execute->cmds - 1) 
        if (is_builtin(shell->token->args[0])) //last cmd and builtin - do in parent
        {
            single_builtin(shell);
            *cmd_count = *cmd_count + 1;
        }
}
*/ 