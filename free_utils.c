/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:21:47 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 17:56:57 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(t_data *data, t_cmd *cmd_list)
{
	if (data->pwd)
		free(data->pwd);
	if (data->cmd_line)
		free(data->cmd_line);
	if (data->cmd_list)
		free_cmds(cmd_list, NULL);
	if (data->env_cpy)
		free_matrix(data->env_cpy);
	free(data);
}
