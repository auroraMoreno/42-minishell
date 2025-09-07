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
		return (-1);
	if (i > start)
		nbr++;
	return (nbr);
}

char	**just_one_token(char *cmd_trimmed)
{
	char	**tokens;

	tokens = (char **)malloc(2 * sizeof(char *));
	if (!tokens)
	{
		free (cmd_trimmed);
		return (NULL);
	}
	tokens[0] = ft_strdup(cmd_trimmed);
	if (!tokens[0])
	{
		free (cmd_trimmed);
		free (tokens);
		return (NULL);
	}
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
	token = ft_strtrim(to_trim, " \t\r\n\v\f");
	free(to_trim);
	if (!token)
		return (NULL);
	return (token);
}

char	**tokens_split(char *cmd, int token_nbr, int *delimiters_pos)
{
	int		i;
	int		j;
	char	**tokens;

	tokens = (char **)malloc((token_nbr + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (i < token_nbr)
	{
		tokens[i] = push_token(cmd, delimiters_pos[j], delimiters_pos[j + 1]);
		if (!tokens[i] || tokens[i][0] == '\0')
		{
			if (tokens[i])
				free(tokens[i]);
			tokens[i] = NULL;
			free_matrix(tokens);
			return (NULL);
		}
		i++;
		j++;
	}
	tokens[i] = NULL;
	return (tokens);
}

char	**input_to_tokens(char *cmd)
{
	char	*cmd_trimmed;
	int		token_nbr;
	int		*delimiters_pos;
	char	**tokens;

	delimiters_pos = NULL;
	cmd_trimmed = ft_strtrim(cmd, " \t\r\n\v\f");
	if (!cmd_trimmed)
		return (NULL);
	token_nbr = count_tokens(cmd_trimmed);
	if (token_nbr < 1)
		return (free_tkn_maker(token_nbr, cmd_trimmed, delimiters_pos));
	if (token_nbr == 1)
		return (just_one_token(cmd_trimmed));
	delimiters_pos = (int *)malloc((token_nbr + 1) * sizeof(int));
	if (!delimiters_pos)
		return (free_tkn_maker(token_nbr, cmd_trimmed, NULL));
	if (find_delimiters(cmd_trimmed, token_nbr, delimiters_pos) == -1)
		return (free_tkn_maker(token_nbr, cmd_trimmed, delimiters_pos));
	tokens = tokens_split(cmd_trimmed, token_nbr, delimiters_pos);
	if (!tokens)
		return (free_tkn_maker(token_nbr, cmd_trimmed, delimiters_pos));
	free_tkn_maker(token_nbr, cmd_trimmed, delimiters_pos);
	return (tokens);
}
