






#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell shell;
	t_token *ls_ptr;
	char	*line;


	// signal(SIGINT, sigint_handler);
	ls_ptr = NULL;
	init_shell(&shell, env);
    
	// t_token *head_token; //for debug
    // head_token = NULL; //for debug
	// init_tokens(&head_token); //for debug

	(void)ac;
	(void)av;

	rl_event_hook = event_hook;


	while ((rl_event_hook != NULL))
	{

		line = readline(GREEN BOLD"minishell>"DEFAULT" ");
		if (line == NULL)
			break ;
		//add_history(line);
		//rl_replace_line((const char *)line, 0);
		//printf("%s (main)\n", line);
		//rl_redisplay();
		if (parse(&ls_ptr, &line) != 0)
			continue ;
		print_list_inbar(&ls_ptr);
		print_list(&ls_ptr);
		// print_list_inbar(&head_token);
		execution_junction(&shell, &ls_ptr);
		// execution_junction(&shell, &head_token); //for debug
		clean_tokens(&shell);
		printf("exit status: %d\n", shell.last_exit_status);
	}


	clean_shell(&shell);

	//rl_clear_history();
	return (0);
}
