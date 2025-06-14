#include "../minishell.h"

int	is_space(char c)
{
	char	*space = " \t\r\n\v\f";
	int		i = 0;

	while(space[i])
	{
		if (c == space[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_delimiter(char c)
{
	char	*delimiter = "\"\'(){}";
	int		i = 0;

	while(delimiter[i])
	{
		if (c == delimiter[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_tokens(char *cmd)
{
	int		nbr;
	bool	delimiter;
	int		i;
	char	delimiter_chr;

	nbr = 0;
	delimiter = false;
	i = -1;
	while (cmd[++i])
	{
		printf("char %d == %c | delimiter == %d && delimiter_chr = %c \n", i, cmd[i], delimiter, delimiter_chr);
		if (is_space(cmd[i]) && delimiter == false && !is_space(cmd[i - 1]))
			nbr++;
		if (is_delimiter(cmd[i]))
		{
			if (delimiter == true)
			{
				if (delimiter_chr == cmd[i])
				{
					delimiter = false;
					if (i < ft_strlen(cmd) - 1 && !is_space(cmd[i + 1]))
						return (0);
				}
			}
			else
			{
				delimiter_chr = cmd[i];
				delimiter = true;
			}
		}
	}
	if (delimiter == true)
		return (0);
	return (++nbr);
}
void	find_delimiters(char *cmd, int token_nbr, int *token_delimiters)
{
	bool	delimiter;
	int		i;
	int		j;
	char	delimiter_chr;

	delimiter = false;
	i = -1;
	j = 1;
	while (++i <= ft_strlen(cmd) && j <= token_nbr)
	{
		if ((is_space(cmd[i]) && delimiter == false && !is_space(cmd[i - 1])) || i == ft_strlen(cmd) - 1)
			token_delimiters[j++] = i;
		if (is_delimiter(cmd[i]))
		{
			if (delimiter == true)
			{
				if (delimiter_chr == cmd[i])
				{
					delimiter = false;
					if (i < ft_strlen(cmd) - 1 && !is_space(cmd[i + 1]))
						return;
				}
			}
			else
			{
				delimiter_chr = cmd[i];
				delimiter = true;
			}
		}
	}
	return ;
}

char	**tokens_split(char *cmd, int token_nbr, int *token_delimiters)
{
	char	**tokens;
	char	*to_trim;
	int		i;

	tokens = (char **)malloc(token_nbr * sizeof(char*));
	if (!tokens)
		return (NULL);
	to_trim = ft_substr(cmd, token_delimiters[0], token_delimiters[1]);
	/*if (!to_trim)
			free (tokens)*/
	tokens[0] = ft_strtrim(to_trim, " ");
	/*if (!tokens[0])
		free (tokens);*/
	free (to_trim);
	i = 1;
	while (i < token_nbr)
	{
		to_trim = ft_substr(cmd, token_delimiters[i] + 1, token_delimiters[i + 1] - token_delimiters[i]);
		/*if (!to_trim[i])
			free_matrix(tokens, i);*/
		tokens[i] = ft_strtrim(to_trim, " ");
		/*if (!tokens[i])
			free_matrix(tokens, i);*/
		free (to_trim);
		i++;
	}
	return(tokens);
}

void	parser(char *cmd)
{
	char	*cmd_trimmed;
	int		token_nbr;
	int		*token_delimiters;
	int		i = 0;
	char	**tokens;

	cmd_trimmed = ft_strtrim(cmd, " ");
	/*if (!cmd_trimmed)
		return (NULL);*/
	token_nbr = count_tokens(cmd_trimmed);
	printf("tokens == %d\n", token_nbr);
	token_delimiters = (int *)malloc((token_nbr + 1) * sizeof(int));
	/*if (!token_delimiters)
		return (0);*/
	token_delimiters[0] = 0;
	find_delimiters(cmd_trimmed, token_nbr, token_delimiters);
	while (i <= token_nbr)
	{
		printf("token delimiters %d = %d\n", i, token_delimiters[i]);
		i++;
	}
	tokens = tokens_split(cmd_trimmed, token_nbr, token_delimiters);
	i = 0;
	while (i < token_nbr)
	{
		printf("token %d = %s\n", i, tokens[i]);
		i++;
	}
	free (token_delimiters);
	free(cmd_trimmed);
	//return (tokens);
}

int	main(void)
{
	char	*cmd;
	//char	**tokens;
	//int		i;

	cmd = readline("> ");
	/*tokens = */parser(cmd);
	/*i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	free (tokens);*/
	return (0);
}