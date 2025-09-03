#include "../minishell.h"

int	check_delimiter(int i, int start, char * cmd, int nbr)
{
	int	j;
	int	fake_start;
	int	aux;
	// uso copias para no alterar los valores de "i", "start" y "nbr"
	j = i;
	fake_start = start;
	aux = nbr;
	check_no_quote(&j, &fake_start, cmd, &aux);
	if (aux > nbr)
		return (i);
	return (-1);
}

int	get_delimiter(int *i, int *start, char *cmd, int *nbr)
{
	int	j;
	int	fake_start;
	int	aux;
	// uso una copia de "nbr" porque en la llamada a la función, nbr es también el iterador de "delimiter_pos"

	j = *i;
	fake_start = *start;
	aux = *nbr;
	check_no_quote(&j, &fake_start, cmd, &aux);
	if (aux == *nbr + 1)
	{
		*i = j;
		*start = fake_start;
	}
	else if ((aux > (*nbr + 1)) && (*i > *start || *i == j))
	{
		*start = *i;
		(*i)--;
	}
	else if ((aux > (*nbr + 1)) && (j > *i))
	{
		*i += (j - *i) / (aux - *nbr);
		*start = *i + 1;
	}
	return (*start);
}

int check_array(int *delimiters_pos, int token_number)
{
	int	i;

	i = 0;
	if (delimiters_pos[i++] != 0)
		return (-1);
	while (i < (token_number + 1))
	{
		//printf("delimiter_por[%d] = %d && delimiter_pos[%d] = %d\n", i, delimiters_pos[i], (i - 1), delimiters_pos[i - 1]);
		if (delimiters_pos[i] <= delimiters_pos[i - 1])
			return (-1);
		i++;
	}
	return (0);
}

int	find_delimiters(char *cmd, int token_nbr, int *delimiters_pos)
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
		printf("NBR = %d\n", nbr);
		printf("	before cmd[i]=%c (i=%d) and cmd[start]=%c (start=%d)\n", cmd[i], i, cmd[start], start);
		if (is_quote(cmd[i]))
			check_quote(&in_quote, &quote_chr, cmd[i]);
		if (!in_quote && (check_delimiter(i, start, cmd, nbr) != -1)) // porque al llamar dos veces a get_delimiters(), la primera modificaría "i" y "start" antes de la segunda
		{
			if (check_delimiter(i, start, cmd, nbr) >= delimiters_pos[nbr - 1])
				delimiters_pos[nbr++] = get_delimiter(&i, &start, cmd, &nbr);
		}
		printf("	after cmd[i]=%c (i=%d) and cmd[start]=%c (start=%d)\n", cmd[i], i, cmd[start], start);
		i++;
	}
	printf("NBR = %d\n", nbr);
	delimiters_pos[token_nbr] = ft_strlen(cmd);
	i = 0;
	while (i <= token_nbr)
	{
		printf("delimiter pos %d = %d\n", i, delimiters_pos[i]);
		i++;
	}
	return (check_array(delimiters_pos, token_nbr));
}
