/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:30:23 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 18:31:05 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		op_count;

	if (*i > *start)
		(*nbr)++;
	op = cmd[*i];
	op_count = 0;
	if (op == '<' || op == '>')
	{
		while (cmd[*i] == op)
		{
			op_count++;
			(*i)++;
		}
		*nbr += op_count / 2 + op_count % 2;
	}
	else
	{
		(*nbr)++;
		(*i)++;
	}
	while (is_space(cmd[*i]))
		(*i)++;
	*start = *i;
	(*i)--;
}

void	check_no_quote(int *i, int *start, char *cmd, int *nbr)
{
	if (is_space(cmd[*i]))
		check_space(i, start, cmd, nbr);
	else if (is_operator(cmd[*i]))
		check_operator(i, start, cmd, nbr);
}
