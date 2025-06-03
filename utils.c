/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:08:59 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/02 12:18:06 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// To-Do: init env 

char *ft_find_equal_sign(char *str)
{
    char *substr;
    int i = 0;

    substr = (char *)malloc(sizeof(char) * ft_strlen(str));

    while(str[i] != '=')
    {
        substr[i] = str[i];
        i++;
    }
    substr[i] = '\0';

    return(substr);
}

t_list *ft_process_env_values(char *key_val)
{
    t_env *env;
    t_list *new;
    
    env = (t_env *)malloc(sizeof(t_env));
    
    if(!env)
        return (0);
    
    //voy hasta el igual 
    env->key = ft_find_equal_sign(key_val); // TO-DO: free de esto,
    // voy hasta despues del igual:
    env->value = ft_substr(key_val, ft_strlen(env->key) + 2 ,ft_strlen(key_val) - ft_strlen(env->key) + 1);
    // creo nuevo nodo de la lista
    new = ft_lstnew(env);
    //devuelvo ese nuevo nodo 
    return (new);
}


t_list *ft_init_env(char *envp[])
{
    int i;
    // malloc env
    t_list *first;
    t_list *new;

    i = 0;

    while(envp[i])
    {
        //procesamos el envp[i]
        new = ft_process_env_values(envp[i]);
        if(!new)
            ft_error("error en env");
        // add  la lista
        ft_lstadd_back(&first, new);
        i++;
    }
    //cuando hago aqui return new 
    return (first);
}
