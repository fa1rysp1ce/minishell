






#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell shell;
	// t_token *ls_ptr;
	// char	*line;


	signal(SIGINT, sigint_handler);
	// ls_ptr = NULL;
	init_shell(&shell, env);
    
	t_token *head_token; //for debug
    head_token = NULL; //for debug

	(void)ac;
	(void)av;
	init_tokens(&head_token); //for debug


	// /*
	// while (1)
	{
		// line = readline(GREEN BOLD"minishell>"DEFAULT" ");
		//add_history(line);
		//rl_replace_line((const char *)line, 0);
		//printf("%s (main)\n", line);
		//rl_redisplay();
		// if (parse(&ls_ptr, &line) != 0)
			// continue ;
		// print_list_inbar(&ls_ptr);
		// execution_junction(&shell, &ls_ptr);
		// print_list_inbar(&head_token);
		execution_junction(&shell, &head_token); //for debug
		clean_tokens(&shell);
		printf("exit status: %d\n", shell.last_exit_status);
	}
	// */

	// execution_junction(&shell, &head_token); //for debug


	// clean_tokens(&shell);

	clean_shell(&shell);

	//rl_clear_history();
	return (0);
}
