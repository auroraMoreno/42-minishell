/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/06 15:27:38 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_export(char *var_name[], t_data data)
{

    t_list *curr;
    t_env *env; 
    t_list *new;
    int i;
    
    // export no args
    if(!var_name) 
    {
        
      curr = data.env;
      while(curr)
      { 
        env = curr->content; 
        printf("declare -x %s=\"%s\" \n",env->key, env->value);
        curr = curr->next;
      }  
    }    
    else
    {
        //si export + var_name="value"
        i = 0;
        while(var_name[i])
        {
            new = ft_process_env_values(var_name[i]); // TO-DO: quitarles las comillas del final 
            if(!new)
                ft_error("error en set var");
            ft_lstadd_back(&data.env, new);
            i++;
        }        
        // si export + var_name
        //si export + $var_name DUDA
    }
    return (0);
}
