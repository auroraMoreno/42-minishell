#include "../minishell.h"

int	count_tokens(char *cmd)
{
	int		nbr;
	int		i;
	int		start;
	bool	in_quote;
	char	quote_chr;

	nbr = 0;
	i = 0;
	start = 0;
	in_quote = false;
	quote_chr = 0;
	while (cmd[i])
	{
		if (is_quote(cmd[i]))
			check_quote(&in_quote, &quote_chr, cmd[i]);
		if (!in_quote)
			check_no_quote(&i, &start, cmd, &nbr);
		i++;
	}
	if (in_quote == true)
		return (0);
	if (i > start)
		nbr++;
	return (nbr);
}
char	**just_one_token(char *cmd_trimmed)
{
	char	**tokens;

	tokens = (char **)malloc(2 * sizeof(char *));
	if (!tokens)
		return (NULL);
	tokens[0] = ft_strdup(cmd_trimmed);
	if (!tokens[0])
		return (NULL);
	free(cmd_trimmed);
	tokens[1] = NULL;
	return (tokens);
}

char	*push_token(char *cmd, int start, int end)
{
	int		size;
	char	*to_trim;
	char	*token;

	size = end - start;
	to_trim = ft_substr(cmd, start, size);
	if (!to_trim)
		return (NULL);
	token = ft_strtrim(to_trim, " ");
	free(to_trim);
	if (!token)
		return (NULL);
	return (token);
}

char	**tokens_split(char *cmd, int token_nbr, int *delimiters_pos)
{
	int		i;
	char	**tokens;

	tokens = (char **)malloc((token_nbr + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < token_nbr)
	{
		tokens[i] = push_token(cmd, delimiters_pos[i], delimiters_pos[i + 1]);
		if (!tokens[i])
		{
			free_matrix(tokens);
			return (NULL);
		}
		i++;
	}
	tokens[token_nbr] = NULL;
	return (tokens);
}

char	**input_to_tokens(char *cmd)
{
	char	*cmd_trimmed;
	int		token_nbr;
	int		*delimiters_pos;
	char	**tokens;

	cmd_trimmed = ft_strtrim(cmd, " ");
	if (!cmd_trimmed)
		return (NULL);
	token_nbr = count_tokens(cmd_trimmed);
	if (!token_nbr)
		return (NULL);
	if (token_nbr == 1)
		return (just_one_token(cmd_trimmed));
	delimiters_pos = (int *)malloc((token_nbr + 1) * sizeof(int));
	find_delimiters(cmd_trimmed, token_nbr, delimiters_pos);
	if (!delimiters_pos)
		return (0);
	tokens = tokens_split(cmd_trimmed, token_nbr, delimiters_pos);
	if (!tokens)
		return (NULL);
	free (cmd_trimmed);
	free (delimiters_pos);
	return (tokens);
}
