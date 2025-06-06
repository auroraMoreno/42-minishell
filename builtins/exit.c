/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:48 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/06 13:07:42 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
 Exit the shell, returning a status of n to the shell’s parent. If n is omitted, the
 exit status is that of the last command executed. Any trap on EXIT is executed
 before the shell terminates.*/
int ft_exit(int status)
{ 
    if(status < 0 || status > 255)
        exit(EXIT_FAILURE);
    //TO-DO: comprobar que status es un status valido?
    exit(status);
    return (status); // TO-DO: quitar eso, exit does not return, considerar union
}