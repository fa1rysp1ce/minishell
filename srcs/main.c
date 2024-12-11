






#include "minishell.h"

extern	int		g_status;

int	main(int ac, char **av, char **env)
{
	t_shell shell;
	t_token *ls_ptr;
	char	*line;
	// int		exit_status;


	ls_ptr = NULL;

	init_shell(&shell, env);
    

	(void)ac;
	 (void)av;
	/*if (av[1] && ft_strcmp(av[1], "-c") == 0)
		if (av[2])
			{
				line = ft_strdup(av[2]);
				parse(&ls_ptr, &line, &shell);
				// print_list_inbar(&ls_ptr);
				execution_junction(&shell, &ls_ptr);
				clean_tokens(&shell);
				exit_status = shell.last_exit_status;
				clean_shell(&shell);

				return (exit_status);
			} */
// signal(SIGINT, SIG_IGN);

	while (1)
	{
		shell.last_exit_status = g_status;
		signal_interactive();
		line = readline(GREEN BOLD"minishell>"DEFAULT" ");
		if (line == NULL)
		{
			shell.last_exit_status = EXIT_SUCCESS;
			break ;
		}
		add_history(line);
		rl_replace_line((const char *)line, 0);
		rl_redisplay();
		if (parse(&ls_ptr, &line, &shell) != 0)
			continue ;
		// print_list_inbar(&ls_ptr);
		 //print_list(&ls_ptr);
		signal_noninteractive();
		execution_junction(&shell, &ls_ptr);
		shell.last_exit_status = g_status;
		clean_tokens(&shell);
		// printf("exit status: %d\n", shell.last_exit_status);
	}

	// exit_status = shell.last_exit_status;
	clean_shell(&shell);

	rl_clear_history();
	return (shell.last_exit_status);
}
