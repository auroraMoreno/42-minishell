/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:20:27 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 20:36:00 by ccarro-d         ###   ########.fr       */
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

int	exec_expansions(t_cmd *cmd_list, t_env *env, int *last_status)
{
	if (cmd_list->argv)
	{
		if (!expand_argv(cmd_list->argv, env, last_status))
			return (0);
	}
	if (cmd_list->assignments)
	{
		if (!expand_asgns(cmd_list->assignments, env, last_status))
			return (0);
	}
	if (cmd_list->redirs)
	{
		if (!expand_redir(cmd_list->redirs, env, last_status))
			return (0);
	}
	return (1);
}
