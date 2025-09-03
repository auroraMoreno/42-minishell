/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:04:00 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/26 01:44:26 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_remove_element(t_list **env_list, char *var_name)
{
    t_list *curr;
    t_list *prev;
    t_env *env;
    
    curr = *env_list;
    prev = NULL;
    while(curr)
    {
        env = (t_env *)curr->content;
        if(!ft_strncmp(env->key, var_name, ft_strlen(var_name) + 1))
        {
             //todo esto es para unlink el estupido nodo 
            if(prev)
                prev->next = curr->next;
            else 
                *env_list = curr->next;
            curr->next = NULL;
            ft_lstdelone(curr, ft_free_env_node);
            return (1);
        }
        prev = curr;
        curr = curr->next;
    }
    return (0);
}


int ft_unset(t_cmd *cmd, t_data *data)
{
    int i; 
    // si var name vacio no pasa nada
    i = 0;
    while(cmd->args[i]) // aqui me llega nada mas que un string
    {
        ft_remove_element(&data->env, cmd->args[i]);
        i++;
    }
    return (0);
}
