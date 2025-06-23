#include "../minishell.h"

	void	parse_input(char *cmd)
{
	char	**tokens;
	t_token	*token_list;

	tokens = divide_in_tokens(cmd);
	//token_list = insert_tokens_in_list(tokens);
	free_matrix(tokens);
	//check_syntax(token_list);
}

int	main(void)
{
	char	*cmd;

	//cmd = readline("> ");
	cmd = "l's -'l|grep \"hello\" ><<>>>>>redir.txt>";
	parse_input(cmd);
	return (0);
}
