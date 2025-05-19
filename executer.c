/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:03 by aumoreno          #+#    #+#             */
/*   Updated: 2025/05/19 20:14:47 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_handle_exe(char *cmd, char *flags, t_built_in_type builtins[])
{

    (void)flags;
    // hacer comprobación de si es built_in
    int i = 0;
    while(i < 7)
    {
        if(!ft_strncmp(builtins[i].built_in_name, cmd, ft_strlen(cmd)))
        {
            
            //printf("%s es un built in \n", cmd);
            builtins[i].foo(cmd, NULL);      
        }
        i++;
    }
    /*if(cmd.is_built_in)
        // si es built in
        // llamar a la función built in 
    else 
        // si no es built in
    */ 
}