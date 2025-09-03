#include "../minishell.h"

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
	return ;
}

void	check_space(int *i, int *start, char *cmd, int *nbr)
{
	if (*i > *start)
		(*nbr)++;
	while (is_space(cmd[*i + 1]))
		(*i)++;
	*start = *i + 1;
	return ;
}

void	check_operator(int *i, int *start, char *cmd, int *nbr)
{
	char	op;
	int 	op_count;

	if (*i > *start)
		(*nbr)++;
	op = cmd[*i];
	op_count = 0;
	if (op == '<' || op == '>') // Agrupa todos los < o > seguidos
	{
		while (cmd[*i] == op)
		{
			op_count++;
			(*i)++;
		}
		// Agrupa de dos en dos
		*nbr += op_count / 2;
		*nbr += op_count % 2;
		*start = *i;
		(*i)--; // porque el while principal hará i++
	}
	else // solo para '|'
	{
		(*nbr)++;
		*start = *i + 1;
	}
}

void	check_no_quote(int *i, int *start, char *cmd, int *nbr)
{
	//printf("NBR = %d\n", *nbr);
	//printf("	before cmd[i]=%c and cmd[start]=%c\n", cmd[*i], cmd[*start]);
	if (is_space(cmd[*i]))
		check_space(i, start, cmd, nbr);
	else if (is_operator(cmd[*i]))
		check_operator(i, start, cmd, nbr);
	//printf("	after cmd[i]=%c and cmd[start]=%c\n", cmd[*i], cmd[*start]);
}
