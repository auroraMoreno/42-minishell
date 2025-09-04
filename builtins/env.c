/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:54 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/04 12:23:31 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_cmd *cmd, t_data *data)
{
    int i = 0;

    if (!data->env_cpy)
        return 0;

    while (data->env_cpy[i])
    {
        ft_putendl_fd(data->env_cpy[i], cmd->fd_out);
        i++;
    }
    return (0);
}