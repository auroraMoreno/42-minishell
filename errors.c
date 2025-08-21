/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:26:52 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/21 12:33:04 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// modificar este método para q le llegue un numero de error 

void ft_error(char *str)
{
    ft_putendl_fd(str,2);
    exit(EXIT_FAILURE);
}