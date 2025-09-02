#include "../minishell.h"

void	parse_input(char *cmd)
{
	char	**tokens;
	t_token	*token_list;
	t_cmd	*cmd_list;

	tokens = input_to_tokens(cmd);
	if (!tokens)
		return ;
	if (!*tokens)
	{
		free_matrix(tokens);
		return ;
	}
	token_list = tokens_in_list(tokens);
	free_matrix(tokens);
	if (!token_list)
		return;
	print_tokens(token_list);
	cmd_list = tokens_to_cmds(token_list);
	free_token_list(token_list);
	if (!cmd_list)
		return ;
	print_cmds(cmd_list);
	cmd_list = free_cmds(cmd_list, NULL);
	return ;
}

int	main(void)
{
	char	*cmd;

	while (1)
	{
		cmd = readline("> ");
		//cmd = "|||||l's -|||||'l|||||gr>ep <<<<<>>\">>>>><<<<<<<\" \"ZZh>>>>ello\" asdf>>>>>>>>>><<>>>>>>redir.txt>";
		//cmd = "echo 'foo\"bar'\">baz\"";
		if (!cmd) break;
		parse_input(cmd);
		free (cmd);
	}
	return (0);
}

// TODO
	// synatx error
	// heredoc tmpfile
	// expansions