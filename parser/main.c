#include "../minishell.h"

void	interactiv_ms(t_env *env, int *last_status)
{
	char	*cmd;
	t_cmd	*cmd_list;

	while (1)
	{
		cmd = readline("> ");
		if (!cmd)
			break ;
		cmd_list = parse_input(env, cmd, last_status);
		free (cmd);
		// executer()
		cmd_list = free_cmds(cmd_list, NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		last_status;
	t_env	*env;

	(void)argv;
	last_status = 0;
	env = extract_env(envp);
	if (argc == 1)
	{
		if (isatty(STDIN_FILENO))
			interactiv_ms(env, &last_status);
		//else
		//	no_interactive_ms(env, &last_status);
	}
	/*else if (argc == 3 && !ft_strncmp(argv[1], "-c", 3))
		run_one_command(argv[2], env, &last_status);
	else if (argc == 2)
		run_script_file(argv[1], env, &last_status);*/
	else
		last_status = 2;
	return (last_status);
}
