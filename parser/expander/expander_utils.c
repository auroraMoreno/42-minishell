/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:20:27 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 18:20:29 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	potential_var(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

size_t	scan_var_name(char *in, int pos)
{
	size_t	len;

	if (!in[pos])
		return (0);
	if (!ft_isalpha(in[pos]) && in[pos] != '_')
		return (0);
	(pos)++;
	len = 1;
	while (ft_isalnum(in[pos]) || in[pos] == '_')
	{
		len++;
		(pos)++;
	}
	return (len);
}

t_env	*find_var(char *var, t_env *env, size_t len)
{
	t_env	*match;

	match = env;
	while (match)
	{
		if (match->key
			&& !ft_strncmp(match->key, var, len)
			&& match->key[len] == '\0')
			return (match);
		match = match->next;
	}
	return (NULL);
}
