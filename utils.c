/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:08:59 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/19 13:17:58 by aumoreno         ###   ########.fr       */
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

char *ft_find_equal_sign(char *str)
{
    char *substr;
    int i = 0;

    substr = (char *)malloc(sizeof(char) * ft_strlen(str));

    if(!substr)
        ft_error("error in malloc");

    while(str[i] != '=')
    {
        substr[i] = str[i];
        i++;
    }
    substr[i] = '\0';

    return(substr);
}

t_list *ft_process_env_values(char *key_val) // tengo que hacer un dup 
{
    t_env *env;
    t_list *new;
    
    env = (t_env *)malloc(sizeof(t_env));
    
    if(!env)
        return (0);
    
    //voy hasta el igual 
    env->key = ft_find_equal_sign(key_val);
    if(!env->key)
        ft_error("Error setting env key");
    // voy hasta despues del igual:
    env->value = ft_substr(key_val, ft_strlen(env->key) + 1 ,ft_strlen(key_val) - ft_strlen(env->key) + 1);
    if(!env->key)
        ft_error("Error setting env value");
    // creo nuevo nodo de la lista
    new = ft_lstnew(env);
    //devuelvo ese nuevo nodo 
    return (new);
}


t_list *ft_init_env(char *envp[]) // El problema está aquí 
{
    int i;
    // malloc env
    t_list *first = NULL;
    t_list *new = NULL;
    char *env_cpy;

    i = 0;

    while(envp[i])
    {
        //procesamos el envp[i]
        env_cpy = ft_strdup(envp[i]);
        new = ft_process_env_values(env_cpy);
        if(!new)
            ft_error("error en env");
        // add  la lista
        ft_lstadd_back(&first, new);
        free(env_cpy);
        i++;
    }
    //cuando hago aqui return new 
    return (first);
}
