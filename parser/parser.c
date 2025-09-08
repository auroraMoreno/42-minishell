#include "../minishell.h"

t_token	*lexer(char *cmd, int *last_status)
{
	char	**tokens;
	t_token	*token_list;

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
	//print_tokens(token_list); // comentar
	if (!check_syntax(token_list, last_status))
	{
		free_token_list(token_list);
		return (NULL);
	}
	return (token_list);
}

t_cmd	*grammar(t_token	*token_list, t_env *env, int *last_status)
{
	t_cmd	*cmd_list;

	cmd_list = tokens_to_cmds(token_list);
	free_token_list(token_list);
	if (!cmd_list)
		return (NULL);
	//print_cmds(cmd_list); //comentar
	if (!expand_cmds(cmd_list, env, last_status))
		return (free_cmds(cmd_list, NULL));
	//printf("\nlista de comandos tras expander y quote removal:\n");
	//print_cmds(cmd_list); //comentar
	//if (!build_hds(cmd_list, env, last_status))
	//	return (free_cmds(cmd_list, NULL));
	return (cmd_list);
}

t_cmd	*parse_input(t_env *env, char *cmd, int *last_status)
{
	t_token	*token_list;
	t_cmd	*cmd_list;

	token_list = lexer(cmd, last_status);
	if (!token_list)
		return (NULL);
	cmd_list = grammar(token_list, env, last_status);
	if (!cmd_list)
		return (NULL);
	return (cmd_list);
}

/*t_cmd	*parse_input(t_env *env, char *cmd, int *last_status)
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
	printf("\nlista de comandos tras expander y quote removal:\n");
	print_cmds(cmd_list); //comentar
	//if (!build_hds(cmd_list, env, last_status))
	//	return (free_cmds(cmd_list, NULL));
	return (cmd_list);
}*/

// TODO
	// saltos de linea en lexet
	//stdin y stdout en t_cmd
	// heredoc tmpfile