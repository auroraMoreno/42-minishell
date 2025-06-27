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

int	is_quote(char c)
{
	char	*quote;
	int		i;

	quote = "\"\'";
	i = 0;
	while (quote[i])
	{
		if (c == quote[i])
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

void	check_quote(bool *in_quote, char *quote_chr, char to_check)
{
	if (*in_quote)
	{
		if (*quote_chr == to_check)
		{
			*in_quote = false;
			*quote_chr = 0;
		}
	}
	else
	{
		*quote_chr = to_check;
		*in_quote = true;
	}
	return;
}

void	check_space(int *i, int *start, char *cmd, int *nbr)
{
	if (*i > *start)
	{
		printf("nbr incrementa por espacio\n");
		(*nbr)++;
	}
	while (is_space(cmd[*i + 1]))
		(*i)++;
	*start = *i + 1;
	return;
}

void	check_operator(int *i, int *start, char *cmd, int *nbr)
{
	char	op;
	int 	op_count;

	if (*i > *start)
	{
		(*nbr)++;
		printf("nbr incrementa por palabra previa al operador\n");
	}
	op = cmd[*i];
	op_count = 0;
	if (op == '<' || op == '>')
	{
		// Agrupa todos los < o > seguidos
		while (cmd[*i] == op)
		{
			op_count++;
			(*i)++;
		}
		// Agrupa de dos en dos
		if (op_count > 2)
			printf("nbr incrementa por operadores concatenados\n");
		else if (op_count > 0)
			printf("nbr incrementa por operador\n");
		*nbr += op_count / 2;
		*nbr += op_count % 2;
		*start = *i;
		(*i)--; // porque el while principal hará i++
	}
	else // solo para '|'
	{
		(*nbr)++;
		printf("nbr incrementa por operador\n");
		*start = *i + 1;
	}
}

void	check_no_quote(int *i, int *start, char *cmd, int *nbr)
{
	if (is_space(cmd[*i]))
		check_space(i, start, cmd, nbr);
	else if (is_operator(cmd[*i]))
		check_operator(i, start, cmd, nbr);
}

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
		printf("char %d == %c | start %d == %c | in_quote == %d && quote_chr = %c && nbr==%d \n", i, cmd[i], start, cmd[start], in_quote, quote_chr, nbr);
		if (is_quote(cmd[i]))
			check_quote(&in_quote, &quote_chr, cmd[i]);
		if (!in_quote)
			check_no_quote(&i, &start, cmd, &nbr);
		printf("nbr = %d\n", nbr);
		i++;
	}
	if (in_quote == true)
		return (0);
	if (i > start)
		nbr++;
	return (nbr);
}

int	check_delimiter(int *i, int *start, char *cmd, int *nbr)
{
	int	j;
	int	fake_start;
	int	aux;
	// uso copias para no alterar los valores de "i", "start" y "nbr"
	j = *i;
	fake_start = *start;
	aux = *nbr;
	check_no_quote(&j, &fake_start, cmd, &aux);
	if (aux > *nbr)
		return (*i);
	return (-1);
}

int	get_delimiter(int *i, int *start, char *cmd, int *nbr)
{
	int	j;
	int	fake_start;
	int	aux;
	// uso una copia de "nbr" porque en la llamada a la función, nbr es también el iterador de "delimiter_pos"

	j = *i;
	printf("j = %d && i = %d && start = %d\n", j, *i, *start);
	fake_start = *start;
	aux = *nbr;
	check_no_quote(&j, &fake_start, cmd, &aux);
	printf("aux = %d && nbr = %d\n", aux, *nbr);
	if (aux == *nbr + 1)
	{
		*i = j;
		*start = fake_start;
		printf("SE CUMPLE 2 | i = %d & start = %d\n", *i, *start);
		return (*start);
	}
	else if (aux > *nbr + 1)
	{
		if (*i > *start || *i == j)
		{
			*start = *i;
			(*i)--;
			printf("SE CUMPLE 1 | i = %d & start = %d\n", *i, *start);
		}
		else if (j > *i)
		{
			*i += (j - *i) / (aux - *nbr);
			*start = *i + 1;
		}
		return (*start);
	}
	return (-1);
}

void	find_delimiters(char *cmd, int token_nbr, int *delimiters_pos)
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
	delimiters_pos[nbr++] = 0;
	while (cmd[i] && nbr < token_nbr)
	{
		if (is_quote(cmd[i]))
			check_quote(&in_quote, &quote_chr, cmd[i]);
		if (!in_quote && (check_delimiter(&i, &start, cmd, &nbr) != -1)) // porque al llamar dos veces a get_delimiters(), la primera modificaría "i" y "start" antes de la segunda
		{
			if (check_delimiter(&i, &start, cmd, &nbr) >= delimiters_pos[nbr - 1])
				delimiters_pos[nbr++] = get_delimiter(&i, &start, cmd, &nbr);
		}	
		i++;
	}
	delimiters_pos[token_nbr] = ft_strlen(cmd);
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

char*	push_token(char *cmd, int start, int end)
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

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return;
}

char	**tokens_split(char *cmd, int token_nbr, int *delimiters_pos)
{
	int		i;
	char	**tokens;

	tokens = (char **)malloc((token_nbr + 1) * sizeof(char*));
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

char	**divide_in_tokens(char *cmd) // cambiar nombre por get_tokens
{
	char	*cmd_trimmed;
	int		token_nbr;
	int		*delimiters_pos;
	char	**tokens;
	int		i = 0;

	cmd_trimmed = ft_strtrim(cmd, " ");
	if (!cmd_trimmed)
		return (NULL);
	printf("\ncmd_trimmed = %s\n\n", cmd_trimmed);
	token_nbr = count_tokens(cmd_trimmed);
	printf("nbr of tokens == %d\n", token_nbr);
	if (!token_nbr)
		return (NULL);
	if (token_nbr == 1)
		return (just_one_token(cmd_trimmed));
	delimiters_pos = (int *)malloc((token_nbr + 1) * sizeof(int));
	find_delimiters(cmd_trimmed, token_nbr, delimiters_pos);
	if (!delimiters_pos)
		return (0);
	while (i <= token_nbr)
	{
		printf("token delimiters %d = %d\n", i, delimiters_pos[i]);
		i++;
	}
	tokens = tokens_split(cmd_trimmed, token_nbr, delimiters_pos);
	if (!tokens)
		return (NULL);
	i = 0;
	while (i <= token_nbr)
	{
		printf("token %d = %s\n", i, tokens[i]);
		i++;
	}
	free (cmd_trimmed);
	free (delimiters_pos);
	return (tokens);
}
