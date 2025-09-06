#include "../minishell.h"

int	set_var(t_env *env, char *envp)
{
	int	i;
	size_t	equal_pos;
	size_t		pos_to_end;

	if (!env || !envp)
		return (0);
	i = 0;
	equal_pos = 0;
	while (envp[i] && envp[i] != '=')
	{
		equal_pos++;
		i++;
	}
	if (equal_pos == ft_strlen(envp))
		return (0);
	env->key = ft_substr(envp, 0, equal_pos++);
	if (!env->key)
		return (0);
	pos_to_end = ft_strlen(envp) - equal_pos;
	env->value = ft_substr(envp, equal_pos, pos_to_end);
	if (!env->value)
	{
		free (env->key);
		return (0);
	}
	env->next = NULL;
	return (1);
}

t_env	*extract_env(char **envp)
{
	t_env	*env;
	t_env	*head;
	int		i;

	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!env)
			return (NULL);
		if (!set_var(env, envp[0]))
		{
			free_env(head, env);
			return (NULL);	
		}
		if (!list_vars(env, head))
		{
			free_env(head, env);
			return (NULL);
		}
		i++;
	}
	return (head);
}

t_cmd	*parse_input(char *cmd, int *last_status)
{
	char	**tokens;
	t_token	*token_list;
	t_cmd	*cmd_list;

	tokens = input_to_tokens(cmd);
	if (!tokens || !*tokens)
	{
		if (tokens)
			free_matrix(tokens);
		return (NULL);
	}	
	token_list = tokens_in_list(tokens);
	free_matrix(tokens);
	if (!token_list)
		return (NULL);
	print_tokens(token_list); // comentar
	if (!check_syntax(token_list, last_status))
	{
		free_token_list(token_list);
		return (NULL);
	}
	cmd_list = tokens_to_cmds(token_list);
	free_token_list(token_list);
	if (!cmd_list)
		return (NULL);
	print_cmds(cmd_list); //comentar
	if (!expand_cmds(cmd_list, env, last_status))
		return (free_cmds(cmd_list, NULL));
	if (!build_hds(cmd_list, env, last_status))
		return (free_cmds(cmd_list, NULL));
	return (cmd_list);
}

void	interactiv_ms(t_env env, int *last_status)
{
	char	*cmd;
	t_cmd	*cmd_list;

	while (1)
	{
		cmd = readline("> ");
		if (!cmd)
			break ;
		cmd_list = parse_input(cmd, &last_status);
		free (cmd);
		// executer()
		cmd_list = free_cmds(cmd_list, NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		last_status;
	t_env	*env;

	last_status = 0;
	env = extract_env(envp);
	if (argc == 1)
	{
		if (isatty(STDIN_FILENO))
			interactiv_ms(env, &last_status)
		else
			no_interactive_ms(env, &last_status);
	}
	else if (argc == 3 && !ft_strncmp(argv[1], "-c", 3))
		run_one_command()
	else if (argc == 2)
		run_script_file();
	else
		last_status = 2;
	return (last_status);
}

// TODO
	// synatx error
	// heredoc tmpfile
	// expansions