/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:22:44 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 18:22:46 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	var_len(char *in, int *pos, t_env *env)
{
	size_t	len;
	t_env	*var_in_env;

	len = scan_var_name(in, *pos);
	if (!len)
		return (0);
	var_in_env = find_var(in + *pos, env, len);
	*pos += (int)len;
	if (!var_in_env || !var_in_env->value)
		return (0);
	return (ft_strlen(var_in_env->value));
}

size_t	digits_len(int nbr)
{
	size_t			len;
	unsigned int	n;

	len = 1;
	if (nbr < 0)
	{
		len++;
		n = (unsigned int)(-(long long)nbr);
	}
	else
		n = (unsigned int)nbr;
	while (n >= 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	quote_status(char c, bool *in_quote, t_quote_type *q_type, size_t *len)
{
	if (*in_quote == true)
	{
		if ((*q_type == SINGLE_QUOTE && c == '\'')
			|| (*q_type == DOUBLE_QUOTE && c == '"'))
		{
			*in_quote = false;
			*q_type = NO_QUOTE;
		}
		else
			(*len)++;
	}
	else
	{
		*in_quote = true;
		if (c == '\'')
			*q_type = SINGLE_QUOTE;
		else
			*q_type = DOUBLE_QUOTE;
	}
	return ;
}

size_t	handle_dollar_len(char *in, int *i, t_env *env, int *last_status)
{
	size_t	len;

	if (!in[*i + 1] || !potential_var(in[*i + 1]))
		return (1);
	(*i)++;
	if (in[*i] == '?')
		return (digits_len(*last_status));
	len = var_len(in, i, env);
	(*i)--;
	return (len);
}

size_t	expansion_len(char *in, t_env *env, int *last_status)
{
	int				i;
	bool			in_quote;
	t_quote_type	quote_type;
	size_t			len;

	i = 0;
	in_quote = false;
	quote_type = NO_QUOTE;
	len = 0;
	while (in[i])
	{
		if (is_quote(in[i]))
			quote_status(in[i], &in_quote, &quote_type, &len);
		else if (in[i] == '$' && quote_type != SINGLE_QUOTE)
			len += handle_dollar_len(in, &i, env, last_status);
		else
			len++;
		i++;
	}
	return (len);
}
