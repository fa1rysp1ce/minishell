/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilazar <ilazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:46:05 by ilazar            #+#    #+#             */
/*   Updated: 2024/11/20 18:38:33 by ilazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 

#include "libft.h"
#include "safe_malloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

//#include "libftplus/includes/libft.h"   ///to take care of
//#include "safe_malloc/safe_malloc.h"

#define GREEN "\033[32m"
#define BOLD "\033[1m"
#define DEFAULT "\033[0m"

# define CMD 		0
# define PIPE	 	1
# define IN 		2
# define HDOC	 	3
# define OUT 		4
# define OUT_APP 	5

#define EXIT_FAILURE 	1
#define EXIT_SUCCESS 	0
#define MALLOC_ERROR 	-1
#define EXEC_ERROR 		-2

typedef struct s_token
{
    char **args;
	int type;
	struct s_token *next;
} t_token;

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
} t_execute;


//##########parsing##########
//parse.c:
int		parse(t_token **start, char **line);
int		cmd_split(char const *s, char ***strarr);
int		fill_list(char **strarr, t_token **list);

//chck_input.c
int		check_input(char *s);
int		is_op(char c);

//variables.c
void	check_vars(char **line);
void	handle_vars(char **line, int i, int len);
char	*replace_var(char **line, int start, int len, char *substr);

//cmd_split.c
int		fill_arr(char const *s, char ***strarr, int ccount);
int		ft_ccount(char const *s);

//fill_list.c
int		eval_str(char **strarr, t_token **list);
int		handle_commands(char **strarr, int pos, t_token **list);
int		handle_redirec(char *str, char **strarr, int pos, t_token **list);
int		handle_output(char *str, char **strarr, int pos, t_token **list);
int		pipe_token(char **strarr, int pos, t_token **list);

//nodes.c
void	*add_node(t_token **node);
t_token	*find_last(t_token **list);
void	print_list(t_token **list);
void	free_list(t_token **list);

//exit_funcs.c
void	free_split(char **arr, int last, char *s);
void	free_input(char *s,  char *statement);
void	exit_fill_list(char **strarr, int pos, t_token **list);




//##########execution##########
//exec_paths
char	*get_cmd_path(t_shell *shell);


//nodes
t_token	*add_node_inbar(t_token **node);
void    init_tokens(t_token **head);
void    clean_tokens(t_token **head_token);
//remember to remove the jake_nodes file from the makefile


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
