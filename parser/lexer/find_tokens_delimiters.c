/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tokens_delimiters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:32:13 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 18:33:28 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_delimiter(int i, int start, char *cmd, int nbr)
{
	int	j;
	int	fake_start;
	int	aux;

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

int	check_array(int *delimiters_pos, int token_number)
{
	int	i;

	i = 0;
	if (delimiters_pos[i++] != 0)
		return (-1);
	while (i < (token_number + 1))
	{
		if (delimiters_pos[i] <= delimiters_pos[i - 1])
			return (-1);
		i++;
	}
	return (0);
}

int	fill_delimiters_core(char *cmd, int token_nbr, int *delimiters_pos)
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
		if (!in_quote && check_delimiter(i, start, cmd, nbr) != -1)
		{
			if (check_delimiter(i, start, cmd, nbr) >= delimiters_pos[nbr - 1])
				delimiters_pos[nbr++] = get_delimiter(&i, &start, cmd, &nbr);
		}
		i++;
	}
	return (nbr);
}

int	find_delimiters(char *cmd, int token_nbr, int *delimiters_pos)
{
	int	nbr;

	nbr = fill_delimiters_core(cmd, token_nbr, delimiters_pos);
	(void)nbr;
	delimiters_pos[token_nbr] = ft_strlen(cmd);
	return (check_array(delimiters_pos, token_nbr));
}
