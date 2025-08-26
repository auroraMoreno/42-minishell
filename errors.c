/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:26:52 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/25 23:59:31 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// modificar este método para q le llegue un numero de error 

int ft_formatted_error(char *msg, char *cmd, t_data *data)
{
    if(cmd)
    {
        ft_putstr_fd(cmd, STDERR_FILENO);
        ft_putstr_fd(":", STDERR_FILENO);
    }

    if(msg)
        ft_putstr_fd(msg, STDERR_FILENO);
    ft_putstr_fd("\n",STDERR_FILENO);
    data->exit_status = 1;
    return (1);
}


void ft_error(char *str)
{
    ft_putendl_fd(str,2);
    exit(EXIT_FAILURE);
}