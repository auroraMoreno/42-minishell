/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:04:00 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/06 15:42:05 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_list *ft_find_element(t_list **env_list, char *var_name)
{
    t_list *curr;
    t_list *prev;
    t_env *env;
    
    curr = *env_list;
    prev = NULL;
    while(curr)
    {
        env = curr->content;
        if(!ft_strncmp(env->key, var_name, ft_strlen(var_name) + 1))
        {
             //todo esto es para unlink el estupido nodo 
            if(prev)
                prev->next = curr->next;
            else 
                *env_list = curr->next;
            curr->next = NULL;
            return (curr);
        }
        prev = curr;
        curr = curr->next;
    }
    return (NULL);
}


int ft_unset(char *var_names[], t_data data)
{
    t_list *to_del;

    int i;
    // si var name vacio no pasa nada
    if(var_names)
    {
        i = 0;
        while(var_names[i]) // aqui me llega nada mas que un string
        {
            //encontrar en la lista data.env el var_name[i]
            // apartir de aqui todo va a ir dentro de una funcion a parte: 
            
            to_del = ft_find_element(&(data.env), var_names[i]); //TO_DO: gestion errores si no existe bla bla, hacer same en export
            if(to_del)
            {
                ft_lstdelone(to_del, ft_free_env_node);
                printf("var unset\n");
            }
            else
                ft_error("bash unset: Variable not found.");
            i++;
        }
    }
    
    return (0);
}
