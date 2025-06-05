/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:54 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/04 12:11:36 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_data data) //TO-DO: cambiar esto a t_data
{
    t_list *curr;
    t_env *env; 
      
    curr = data.env;
    while(curr)
    { 
    // t data => t_list env => ese recorro 
    // tengo un metodo init env que le llega un t_list env y envp y devuelve t_list env 
    // cada nodo de t_list env es un tipo t_env  (el content es t_list es tipo void asi que puedo meter lo que yo quiera)
    //
    // key = ft_find_equal_sign(env[i]); // esto me puede servir para el metodo init_env
    // value = ft_substr(env[i], ft_strlen(key) + 2 ,ft_strlen(env[i]) - ft_strlen(key) + 1); // + 1 porq key no tiene el igua, aunq a lo mejor cuenta el null
    env = curr->content; 
    printf("%s=%s\n",env->key, env->value); // TO-DO: arregalar que el valor esté surrounded con ""
    curr = curr->next;
    }  
    return (0);
}