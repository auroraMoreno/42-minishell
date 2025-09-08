/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 12:51:45 by aumoreno         ###   ########.fr       */
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

int	ft_print_export(char **env, t_cmd *cmd)
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
	return (0);
}

void	ft_update_env_value(t_data *data, int index_key, char *key, char *value)
{
	char	*tmp;
	char	*result;

	free(data->env_cpy[index_key]);
	tmp = ft_strjoin(key, "=");
	result = ft_strjoin(tmp, value);
	data->env_cpy[index_key] = result;
	free(tmp);
}

void	ft_free_export(char *key, char *value)
{
	free(key);
	if (value)
		free(value);
}

int	ft_export(t_cmd *cmd, t_data *data)
{
	char	*key;
	char	*value;
	int		index_key;
	int		i;

	if (!cmd->argv[1])
		return (ft_print_export(data->env_cpy, cmd));
	i = 1;
	while (cmd->argv[i])
	{
		if (ft_check_variables(cmd->argv[i]))
		{
			ft_process_values(cmd->argv[i], &key, &value);
			index_key = ft_find_in_env_cpy(data->env_cpy, key);
			if (index_key >= 0 && value)
				ft_update_env_value(data, index_key, key, value);
			else if (index_key == -1)
				data->env_cpy = ft_add_env_cpy(data->env_cpy, key, value);
			ft_free_export(key, value);
		}
		else
			ft_formatted_error("invalid identifier", " -bash: export", data);
		i++;
	}
	return (0);
}
