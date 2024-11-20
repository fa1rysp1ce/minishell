/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:46:05 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/20 13:26:34 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INBAR_EXEC_H
#define INBAR_EXEC_H

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>




#define GREEN "\033[32m"
#define BOLD "\033[1m"
#define DEFAULT "\033[0m"

struct s_execute;

typedef struct s_shell
{
	char				**envc;
	char				**paths;
	int					last_exit_status;
	struct s_execute	*execute;
	struct s_token		**head_token;
	struct s_token		*token;

	
} t_shell;

typedef struct s_heredoc
{
	char	*content;
	size_t	length;
	int     doc_pipe[2];
	int		read_end_open;
	
}	t_heredoc;

typedef struct s_execute
{
	int			*org_fds;
	int			pipes;
	int			cmds;
	int			hdocs;
	int			*pid;
	t_heredoc	*heredocs;
	
	// int		pipe_fd[2][2];
	
} t_execute;

//jake
typedef struct s_token
{
    char **args;
	int type;
    // char *input;      			 // Name of input file for <
    // char *output;    			 // Name of output file for > or >>
    // int is_append;        		 // Flag for >> (1) vs > (0)
    
	//int has_heredoc;     		 // Flag for << (1) or not (0)
    //char *heredoc_delimiter;   // Delimiter for here document if used
    
	struct s_token *next;
	
} t_token;


#define CMD			0
#define PIPE		1
#define IN 			2
#define OUT			3
#define OUT_APP		4
#define HDOC		5


#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define MALLOC_ERROR -1
#define EXEC_ERROR -2



//exec_paths
char	*get_cmd_path(t_shell *shell);


//nodes
t_token	*add_node(t_token **node);
void    init_tokens(t_token **head);
void    clean_tokens(t_token **head_token);


//builtins
int     is_builtin(char *str);
int     execute_builtin(t_shell *shell);
void    exit_cmd(t_shell *shell);
int    export(t_shell *shell, t_token *token);
int    unset(t_shell *shell, t_token *token);
int     env(t_shell *shell);
int     pwd(t_shell *shell);
int     echo(t_token *token);
int     cd(t_shell *shell);
int		change_env(t_shell *shell, char *src, char *dest);

//execution
void	execution_junction(t_shell *shell, t_token **head_token);
int    	count_pipes(t_token **token);
void    single_builtin(t_shell *shell);
void 	child_exec(t_shell *shell, int pipe_fd[2][2], int last_pipe, int cmd_count);

//pipeline
void    pipeline(t_shell *shell);

//pipeline utils
void    next_cmd_token(t_shell *shell);
void    swap_pipes(int *last_pipe, int *new_pipe);
void    close_pipes(int pipe_fd[2][2], int pipe);
void    update_exit_status(t_shell *shell, int status);

//redirection
int    redirection(t_shell *shell);

//redirection utils
void    get_next_redirection(t_token **red_token);
int    save_fds(t_shell *shell);
void    restore_fds(t_shell *shell);

//heredoc
int    process_heredocs(t_shell *shell);
int    count_heredocs(t_shell *shell);


//init shell
void    init_shell(t_shell *shell, char **env);
char	*expand_arg(t_shell *shell, char *arg);


//clean free
void 	clean_shell(t_shell *shell);
void    clean_exec(t_shell *shell);
void    clean_heredocs(t_execute *exec);
void    free_2d_charr(char **arr);


//errors
void    exit_error(char *str);
void    error_msg(char *name, char *msg);
int    exit_malloc_err(t_shell *shell);
int    abort_exec(char *msg, t_shell *shell);


//debug
void    print_2darray(char **arr);




#endif