/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:02:06 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 13:38:23 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_errors(int err_number, t_data *data)
{
	if (err_number == EACCES)
		return (ft_formatted_error("Permission denied", "-bash: cd", data));
	else if (err_number == ENOENT)
		return (ft_formatted_error("No such file or directory",
				"-bash: cd", data));
	else if (err_number == ENOTDIR)
		return (ft_formatted_error("Not a directory", "-bash: cd", data));
	return (ft_formatted_error(strerror(err_number), "-bash: cd", data));
}

char	*ft_cd_go_home(char **env_cpy, char *path)
{
	int	i;

	path = NULL;
	i = 0;
	while (env_cpy[i])
	{
		if (!ft_strncmp(env_cpy[i], "HOME", 4))
		{
			path = env_cpy[i] + 5;
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	ft_find_env_index(char **env_cpy, const char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env_cpy[i])
	{
		if (!ft_strncmp(env_cpy[i], key, key_len)
			&& env_cpy[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_update_env(char **env_cpy, char *key, char *value)
{
	char		*new_entry;
	char		*tmp;
	int			idx;

	idx = ft_find_env_index(env_cpy, key);
	new_entry = ft_strjoin(key, "=");
	tmp = ft_strjoin(new_entry, value);
	free(new_entry);
	if (idx >= 0)
	{
		free(env_cpy[idx]);
		env_cpy[idx] = tmp;
	}
	else
		env_cpy = ft_add_env_cpy(env_cpy, key, value);
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	*old_path;
	char	*new_path;

	path = NULL;
	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (ft_formatted_error("path not found", "pwd", data));
	if (!cmd->argv[1])
	{
		path = ft_cd_go_home(data->env_cpy, path);
		if (!path)
			ft_cd_no_args(old_path, data);
	}
	else if (cmd->argv[2])
		return (ft_cd_too_many_args(old_path, data));
	else
		path = cmd->argv[1];
	if (chdir (path) == -1)
		return (ft_cd_chdir_error(old_path, data));
	new_path = getcwd(NULL, 0);
	if (!new_path)
		return (ft_cwd_not_found_error(old_path, data));
	ft_cd_updt_and_free(data, new_path, old_path);
	return (0);
}
