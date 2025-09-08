/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:26:52 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 10:02:40 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_formatted_error(char *msg, char *cmd, t_data *data)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(":", STDERR_FILENO);
	}
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->exit_status = 1;
	return (1);
}

void	ft_error_and_free(char *msg, int code, t_data *data, t_cmd *cmd_list)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	ft_free_all(data, cmd_list);
	exit(code);
}
