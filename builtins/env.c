/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:54 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/06 15:57:09 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_data data)
{
    t_list *curr;
    t_env *env; 
      
    curr = data.env;
    while(curr)
    { 
    env = curr->content; 
    printf("%s=%s\n",env->key, env->value); // TO-DO: arregalar que el valor esté surrounded con ""
    curr = curr->next;
    }  
    return (0); //TO-DO no devuelve nada 
}