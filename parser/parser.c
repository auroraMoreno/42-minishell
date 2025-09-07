#include "../minishell.h"

t_cmd	*parse_input(t_env *env, char *cmd, int *last_status)
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

// TODO
	// expansions
	// heredoc tmpfile