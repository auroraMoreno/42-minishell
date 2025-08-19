#include "../minishell.h"

void	parse_input(char *cmd)
{
	char	**tokens;
	t_token	*token_list;
	//t_cmd	*cmd_list;

	tokens = input_to_tokens(cmd);
	if (!*tokens)
		return;
	token_list = tokens_in_list(tokens);
	free_matrix(tokens);
	//cmd_list = tokens_to_cmds(token_list);
	//free_list(token_list); // TODO: Por hacer función
	//check_syntax(token_list);
}

int	main(void)
{
	char	*cmd;

	//cmd = readline("> ");
	//cmd = "|||||l's -|||||'l|||||gr>ep <<<<<>>\">>>>><<<<<<<\" \"ZZh>>>>ello\" asdf>>>>>>>>>><<>>>>>>redir.txt>";
	cmd = "echo 'foo\"bar'\">baz\"";
	parse_input(cmd);
	return (0);
}
