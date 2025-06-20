#include "../minishell.h"

int	is_space(char c)
{
	char	*space;
	int		i;

	space = " \t\r\n\v\f";
	i = 0;
	while (space[i])
	{
		if (c == space[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_delimiter(char c)
{
	char	*delimiter;
	int		i;

	delimiter= "\"\'(){}";
	i = 0;
	while (delimiter[i])
	{
		if (c == delimiter[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_operator(char c)
{
	char	*operator;
	int		i;

	operator = ">|<";
	i = 0;
	while (operator[i])
	{
		if (c == operator[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_tokens(char *cmd)
{
	int		nbr;
	bool	in_delimiter;
	bool	in_operator;
	int		i;
	char	delimiter_chr;

	nbr = 0;
	in_delimiter = false;
	in_operator = false;
	i = 0;
	delimiter_chr = 0;
	while (cmd[i])
	{
		printf("char %d == %c | in_operator == %d && in_delimiter == %d && delimiter_chr = %c && nbr==%d \n", i, cmd[i], in_operator, in_delimiter, delimiter_chr, nbr);
		if (is_space(cmd[i]) && (i > 0 && !is_space(cmd[i - 1])) && !in_delimiter)
		{
			printf("nbr incrementa por espacio\n");
			nbr++;
		}
		else if (is_delimiter(cmd[i]))
		{
			if (in_delimiter == true)
			{
				if (delimiter_chr == cmd[i])
				{
					in_delimiter = false;
					delimiter_chr = 0;
				}
			}
			else
			{
				delimiter_chr = cmd[i];
				in_delimiter = true;
			}
		}
		else if (is_operator(cmd[i]) && !in_delimiter)
		{
			if (in_operator == false)
			{
				if (i > 0 && !is_space(cmd[i - 1]))
				{
					nbr++;
					printf("nbr incrementa por operador pegado a texto '%c'\n", cmd[i - 1]);
				}
				in_operator = true;
				if (cmd[i + 1])
				{
					if (is_operator(cmd[i + 1]) && (cmd[i] != cmd[i + 1]))
					{
						nbr++;
						printf("nbr incrementa por operador pegado a operador\n");
					}
					if (!is_operator(cmd[i + 1]))
					{
						in_operator = false;
						if (!is_space(cmd[i + 1]))
						{
							printf("nbr incrementa por texto pegado a operador\n");
							nbr++;
						}
					}
				}
			}
			else
			{
				if (cmd[i + 1] && !is_space(cmd[i + 1]))
				{
					if (is_operator(cmd[i + 1]))
					{
						if (cmd[i] == cmd[i - 1])
							in_operator = false;
						else
						{
							nbr++;
							printf("nbr incrementa por operador pegado a operador\n");
						}
					}
					else
					{
						in_operator = false;
						nbr++;
						printf("nbr incrementa por texto pegado a operadorRR\n");
					}
				}
				else
				{
					in_operator = false;
					if (i == (ft_strlen(cmd) - 1) && cmd[i] != cmd[i - 1] && !is_space(cmd[i - 1]))
						nbr++;
				}
			}		
		}
		printf("nbr = %d\n", nbr);
		i++;
	}
	if (in_delimiter == true)
		return (0);
	return (++nbr);
}
void	delimiters_pos(char *cmd, int token_nbr, int *token_delimiters)
{
	bool	in_delimiter;
	bool	in_operator;
	int		i;
	int		j;
	char	delimiter_chr;

	in_delimiter = false;
	in_operator = false;
	i = 0;
	j = 0;
	delimiter_chr = 0;
	token_delimiters[j++] = i++;
	while (i < (int)ft_strlen(cmd) && j < token_nbr)
	{
		if (is_space(cmd[i]) && (i > 0 && !is_space(cmd[i - 1])) && !in_delimiter)
			token_delimiters[j++] = i;
		else if (is_delimiter(cmd[i]))
		{
			if (in_delimiter == true)
			{
				if (delimiter_chr == cmd[i])
				{
					in_delimiter = false;
					delimiter_chr = 0;
				}
			}
			else
			{
				delimiter_chr = cmd[i];
				in_delimiter = true;
			}
		}
		else if (is_operator(cmd[i]) && !in_delimiter)
		{
			if (in_operator == false)
			{
				if (i > 0 && !is_space(cmd[i - 1]))
				{
					token_delimiters[j++] = i;
				}
				in_operator = true;
				if (cmd[i + 1])
				{
					if (is_operator(cmd[i + 1]) && (cmd[i] != cmd[i + 1]))
					{
						token_delimiters[j++] = i;
						printf("nbr incrementa por operador pegado a operador\n");
					}
					if (!is_operator(cmd[i + 1]))
					{
						in_operator = false;
						if (!is_space(cmd[i + 1]))
						{
							printf("nbr incrementa por texto pegado a operador\n");
							token_delimiters[j++] = i;
						}
					}
				}
			}
			else
			{
				if (cmd[i + 1] && !is_space(cmd[i + 1]))
				{
					if (is_operator(cmd[i + 1]))
					{
						if (cmd[i] == cmd[i - 1])
							in_operator = false;
						else
						{
							token_delimiters[j++] = i;
						}
					}
					else
					{
						in_operator = false;
						token_delimiters[j++] = i;
					}
				}
				else
				{
					in_operator = false;
					if (i == (ft_strlen(cmd) - 1) && cmd[i] != cmd[i - 1])
						token_delimiters[j++] = i;
				}
			}		
		}
		i++;
	}
	printf("ft_strlen(cmd) = %zu\n", ft_strlen(cmd));
	token_delimiters[token_nbr] = (ft_strlen(cmd) - 1);
	return ;
}

char	**tokens_split(char *cmd, int token_nbr, int *token_delimiters)
{
	char	**tokens;
	char	*to_trim;
	int		i;
	printf("dafuq\n");
	tokens = (char **)malloc((token_nbr + 1) * sizeof(char*));
	if (!tokens)
		return (NULL);
	if (token_nbr == 1)
	{
		to_trim = ft_substr(cmd, token_delimiters[0], token_delimiters[1] + 1);
		tokens[0] = ft_strtrim(to_trim, " ");
		free(to_trim);
		tokens[1] = NULL;
		return (tokens);
	}
	else
		to_trim = ft_substr(cmd, token_delimiters[0], token_delimiters[1]);
	/*if (!to_trim)
			free (tokens)*/
	tokens[0] = ft_strtrim(to_trim, " ");
	/*if (!tokens[0])
		free (tokens);*/
	free (to_trim);
	i = 1;
	while (i < token_nbr - 1)
	{
		printf("extract before trim between %d & %d\n", token_delimiters[i], token_delimiters[i + 1]);
		if (is_space(cmd[token_delimiters[i]]))
		{
			to_trim = ft_substr(cmd, token_delimiters[i] + 1, token_delimiters[i + 1] - token_delimiters[i] - 1);
		}
		else
		{
			if (token_delimiters[i] == token_delimiters[i + 1])
			token_delimiters[i + 1] += 1;
			to_trim = ft_substr(cmd, token_delimiters[i], token_delimiters[i + 1] - token_delimiters[i]);
		}
			printf("new token_delimiters[i] = %d\n", token_delimiters[i]);
		/*if (!to_trim)
			free_matrix(tokens, i);*/
		tokens[i] = ft_strtrim(to_trim, " ");
		/*if (!tokens[i])
			free_matrix(tokens, i);*/
		free (to_trim);
		i++;
	}
	to_trim = ft_substr(cmd, token_delimiters[i], token_delimiters[i + 1] - token_delimiters[i] + 1);
	tokens[token_nbr - 1] = ft_strtrim(to_trim, " ");
	free (to_trim);
	tokens[token_nbr] = NULL;
	return(tokens);
}

char	**divide_in_tokens(char *cmd)
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
	if (!token_nbr)
		return (NULL);
	printf("tokens == %d\n", token_nbr);
	token_delimiters = (int *)malloc((token_nbr + 1) * sizeof(int));
	/*if (!token_delimiters)
		return (0);*/
	token_delimiters[0] = 0;
	delimiters_pos(cmd_trimmed, token_nbr, token_delimiters);
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
	return (tokens);
}
