/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:04:00 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 09:54:05 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_remove_element(char ***env_cpy, char *var_name)
{
	char	**new_env;
	char	**old_env;
	int		j;
	int		i;

	old_env = *env_cpy;
	new_env = malloc(sizeof(char *) * ft_get_env_size(old_env));
	if (!new_env)
		return (-1);
	i = 0;
	j = 0;
	while (old_env[i])
	{
		if (ft_strncmp(old_env[i], var_name, ft_strlen(var_name)) != 0
			|| old_env[i][ft_strlen(var_name)] != '=')
			new_env[j++] = old_env[i];
		else
			free(old_env[i]);
		i++;
	}
	new_env[j] = NULL;
	free(old_env);
	*env_cpy = new_env;
	return (0);
}

int	ft_unset(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (ft_remove_element(&(data->env_cpy), cmd->argv[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
