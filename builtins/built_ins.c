/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:09:08 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 00:31:26 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	ft_check_built_in(char *cmd, char *built_ins[])
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(cmd, built_ins[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_built_ins(t_cmd *cmd, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (!ft_strcmp("echo", cmd->argv[0]))
		exit_code = ft_echo(cmd);
	else if (!ft_strcmp("cd", cmd->argv[0]))
		exit_code = ft_cd(cmd, data);
	else if (!ft_strcmp("pwd", cmd->argv[0]))
		exit_code = ft_pwd(cmd, data);
	else if (!ft_strcmp("export", cmd->argv[0]))
		exit_code = ft_export(cmd, data);
	else if (!ft_strcmp("unset", cmd->argv[0]))
		exit_code = ft_unset(cmd, data);
	else if (!ft_strcmp("env", cmd->argv[0]))
		exit_code = ft_env(cmd, data);
	else if (!ft_strcmp("exit", cmd->argv[0]))
		exit_code = ft_exit(cmd, data);
	return (exit_code);
}
