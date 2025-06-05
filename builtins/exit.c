/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:48 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/04 13:59:31 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
 Exit the shell, returning a status of n to the shell’s parent. If n is omitted, the
 exit status is that of the last command executed. Any trap on EXIT is executed
 before the shell terminates.*/
int ft_exit(int status)
{
    exit(status);
    return (status); // quitar eso, exit does not return 
}