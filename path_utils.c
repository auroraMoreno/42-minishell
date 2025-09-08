/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:13:01 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 12:14:21 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_path_not_found(char *key, t_cmd *cmd_list, t_data *data)
{
	free(key);
	ft_error_and_free("command not found", 127, data, cmd_list);
}

char	*ft_build_path(char *key, t_cmd *cmd, t_data *data, t_cmd *cmd_list)
{
	char	*cwd;
	char	*temp;
	char	*path;

	if (cmd->argv[0][0] == '/')
		path = cmd->argv[0];
	else if (cmd->argv[0][0] == '.')
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
			ft_error_and_free("getcwd error", 1, data, cmd_list);
		path = ft_strjoin(cwd, "/");
		if (!path)
			ft_error_and_free("malloc error", 1, data, cmd_list);
		temp = ft_strjoin(path, cmd->argv[0]);
		free(path);
		path = temp;
		free(cwd);
	}
	else
		path = get_route(cmd->argv[0], data->env_cpy, data);
	if (!path)
		ft_path_not_found(key, cmd_list, data);
	return (path);
}
