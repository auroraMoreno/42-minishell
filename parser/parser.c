#include "../minishell.h"

bool	is_space(char c)
{
	char	*space = " \t\r\n\v\f";
	int		i = 0;

	while(space[i])
	{
		if (c == space[i])
			return (true);
		i++;
	}
	return (false);
}

char	**divide_in_tokens(char *cmd)
{
	char	*space = " \t\r\n\v\f";
	char	*token_delimiter ="\"\'(){}";
	int		cmd_lenght;
	int		cmd_pos = 0;

	cmd_lenght = ft_strlen(cmd);
	while (cmd[cmd_pos])
	{
		while (is_space(cmd[cmd_pos]))
			cmd_pos++;
	}
}

char	**parser(char *cmd)
{
	char	**tokens;
	bool	in_token;

	tokens = divide_in_tokens(cmd);
	return (tokens);
}

int	main(int argc, char **argv)
{
	char	*cmd;

	cmd = readline("> ");
	printf("%s\n", cmd);
	return (0);
}