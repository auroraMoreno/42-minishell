/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:08:59 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/03 11:14:01 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;
        
    while(s1[i] || s2[i])
    {
        if(s1[i] == s2[i])
            i++;
        else if(s1[i] != s2[i])
		    return (1);
    }
    return (0);
}


void ft_free_matrix(char **matrix)
{
    int i;

    if (!matrix)
        return;
    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}



t_list *ft_process_env_values(char *key_val) // tengo que hacer un dup 
{
    t_env *env;
    t_list *new;

    env = (t_env *)malloc(sizeof(t_env));
    if(!env)
        return (0);
    ft_process_values(key_val, &env->key, env->value);
    if(!env->key)
    {
        //TO-DO: free memory
        return (0);
    }
    // creo nuevo nodo de la lista
    new = ft_lstnew(env);
    
    if(!new)
    {
        //TO-DO: free

        return (0);
    }
    //devuelvo ese nuevo nodo 
    return (new);
}
