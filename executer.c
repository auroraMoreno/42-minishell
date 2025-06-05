/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:03 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/04 12:32:38 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_handle_exe(char *cmd, char *flags, t_built_in_type builtins[], t_data data)
{

    (void)flags;
    // hacer comprobación de si es built_in
    //TO-DO: Hacer comprobacion de nulls y demas y lanzar errors, dentro del bucle tmb 
    int i = 0;
    while(i < 7)
    {
        if(!ft_strncmp(builtins[i].built_in_name, cmd, ft_strlen(cmd)))
        {
            if(!ft_strncmp("env", cmd, ft_strlen(cmd)))
                builtins[i].foo(data.env);      
            else if(!ft_strncmp("export", cmd, ft_strlen(cmd)))
            {
                char *args[] = {"A=\"Valor1\"","B=\"Valor2\"", NULL};
                builtins[i].foo(args , data.env);
            }
            else if(!ft_strncmp("unset", cmd, ft_strlen(cmd)))
            {
                char *args[] = {"A","B", NULL};
                builtins[i].foo(args , data.env);
            }
            else   
            
                builtins[i].foo("hola que tal", NULL); 
            break;  
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