/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:20:51 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 18:21:02 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_and_rem_quotes(char *in, t_env *env, int *last_status)
{
	size_t	out_len;
	char	*out;

	if (!in || !last_status)
		return (NULL);
	out_len = expansion_len(in, env, last_status);
	out = (char *)ft_calloc(out_len + 1, sizeof(char));
	if (!out)
		return (NULL);
	craft_out(in, out, env, last_status);
	return (out);
}

int	expand_argv(char **argv, t_env *env, int *last_status)
{
	int		i;
	char	*new;

	if (!argv || !*argv)
		return (1);
	if (!last_status)
		return (0);
	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '$') || str_is_quoted(argv[i]))
		{
			new = expand_and_rem_quotes(argv[i], env, last_status);
			if (!new)
				return (0);
			free (argv[i]);
			argv[i] = new;
		}
		i++;
	}
	return (1);
}

int	expand_asgns(t_assign *assgns, t_env *env, int *last_status)
{
	t_assign	*tmp;
	char		*new;

	tmp = assgns;
	while (tmp)
	{
		if (tmp->value
			&& (ft_strchr(tmp->value, '$') || str_is_quoted(tmp->value)))
		{
			new = expand_and_rem_quotes(tmp->value, env, last_status);
			if (!new)
				return (0);
			free (tmp->value);
			tmp->value = new;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	expand_redir(t_redir *redirs, t_env *env, int *last_status)
{
	t_redir	*tmp;
	char	*new;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->target && tmp->redir_type != R_HEREDOC
			&& (ft_strchr(tmp->target, '$') || str_is_quoted(tmp->target)))
		{
			new = expand_and_rem_quotes(tmp->target, env, last_status);
			if (!new)
				return (0);
			free (tmp->target);
			tmp->target = new;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	expand_cmds(t_cmd *cmd_list, t_env *env, int *last_status)
{
	t_cmd	*tmp;

	if (!last_status)
		return (0);
	if (!cmd_list)
		return (1);
	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->argv)
		{
			if (!expand_argv(tmp->argv, env, last_status))
				return (0);
		}
		if (tmp->assignments)
		{
			if (!expand_asgns(tmp->assignments, env, last_status))
				return (0);
		}
		if (tmp->redirs)
		{
			if (!expand_redir(tmp->redirs, env, last_status))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
