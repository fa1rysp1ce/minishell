#ifndef MINISHELL_H
# define MINISHELL_H 

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libftplus/includes/libft.h"

# define GREEN "\033[32m"
# define BOLD "\033[1m"
# define DEFAULT "\033[0m"

# define CMD 0
# define PIPE 1
# define IN 2
# define HDOC 3
# define OUT 4
# define OUT_APP 5

typedef struct s_token
{
	char	**args;
	int		type;
	//char	*input;      // Name of input file for < // array
   // char 	*output;     // Name of output file for > or >>  //array
   // int		heredoc;       // Flag for << (1) or not (0) char //char * array
   // int 	is_append;        // Flag for >> (1) vs > (0)
	void	*next;
} t_token;

//parsing:

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


//execution:

#endif