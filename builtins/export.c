/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 09:42:08 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_process_values(char *key_val, char **key, char **val)
{
	char	*equal;

	*key = ft_get_key(key_val);
	equal = ft_strchr(key_val, '=');
	if (!equal)
		*val = NULL;
	else if (*(equal + 1) == '\0')
		*val = ft_strdup("");
	else
		*val = ft_strdup(equal + 1);
}

void	ft_print_export(char **env, t_cmd *cmd)
{
	int		i;
	char	**sorted_env;

	i = 0;
	sorted_env = ft_sort_alpha(env);
	while (sorted_env[i])
	{
		ft_putstr_fd("declare -x ", cmd->fd_out);
		ft_putstr_fd(sorted_env[i], cmd->fd_out);
		ft_putstr_fd("\n", cmd->fd_out);
		i++;
	}
}

int	ft_export(t_cmd *cmd, t_data *data)
{
	char	*tmp;
	char	*result;
	char	*key;
	char	*value;
	int		index_key;
	int		i;

	if (!cmd->argv[1])
	{
		ft_print_export(data->env_cpy, cmd);
		return (0);
	}
	i = 1;
	while (cmd->argv[i])
	{
		if (ft_check_variables(cmd->argv[i]))
		{
			ft_process_values(cmd->argv[i], &key, &value);
			index_key = ft_find_in_env_cpy(data->env_cpy, key);
			if (index_key >= 0 && value)
			{
				free(data->env_cpy[index_key]);
				tmp = ft_strjoin(key, "=");
				result = ft_strjoin(tmp, value);
				data->env_cpy[index_key] = result;
				free(tmp);
			}
			else if (index_key == -1)
				data->env_cpy = ft_add_env_cpy(data->env_cpy, key, value);
			free(key);
			if (value)
				free(value);
		}
		else
			ft_formatted_error("not a valid identifier", " -bash: export", data);
		i++;
	}
	return (0);
}
