/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:42:05 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/07 18:28:16 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_builtins(t_data *data)
{
	data->built_ins[0] = "echo";
	data->built_ins[1] = "cd";
	data->built_ins[2] = "pwd";
	data->built_ins[3] = "export";
	data->built_ins[4] = "unset";
	data->built_ins[5] = "env";
	data->built_ins[6] = "exit";
}

int	ft_get_env_size(char **env)
{
	int	len;

	len = 0;
	while (*env)
	{
		len++;
		env++;
	}
	return (len);
}

char	**ft_cpy_env(char **env)
{
	int		i;
	int		env_size;
	char	**env_cpy;

	if (!env)
		return (0);
	env_size = ft_get_env_size(env);
	env_cpy = ft_calloc(env_size + 1, sizeof(char *));
	if (!env_cpy)
		return (0);
	i = 0;
	while (env[i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		if (!env_cpy[i])
		{
			free_matrix(env_cpy);
			return (0);
		}
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

void	ft_init_data(t_data *data, char **env)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	g_signal = 0;
	data->env_cpy = ft_cpy_env(env);
	if (!data->env_cpy)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_init_builtins(data);
	data->prompt = "minishell>";
	data->cmd_line = NULL;
	data->pwd = getcwd(NULL, 0);
	data->exit_status = 0;
	data->cmd_list = NULL;
}
