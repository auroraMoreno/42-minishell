/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:37:32 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 13:41:13 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_no_args(char *old_path, t_data *data)
{
	free(old_path);
	return (ft_formatted_error("HOME not set", "-bash: cd ", data));
}

int	ft_cd_too_many_args(char *old_path, t_data *data)
{
	free(old_path);
	return (ft_formatted_error("too many arguments", "-bash: cd ", data));
}

void	ft_cd_updt_and_free(t_data *data, char *new_path, char *old_path)
{
	ft_update_env(data->env_cpy, "OLDPWD", old_path);
	ft_update_env(data->env_cpy, "PWD", new_path);
	free(new_path);
	free(old_path);
}

int	ft_cwd_not_found_error(char *old_path, t_data *data)
{
	free(old_path);
	return (ft_formatted_error("path not found", "pwd", data));
}

int	ft_cd_chdir_error(char *old_path, t_data *data)
{
	free(old_path);
	return (ft_cd_errors(errno, data));
}
