/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:54 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/26 00:14:09 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(t_cmd *cmd, t_data *data)
{
    t_list *curr;
    t_env *env; 
      
    curr = data->env;
    while(curr)
    { 
        env = (t_env *)curr->content; 
        if(env->key && env->value)
        {
            ft_putstr_fd(env->key, cmd->fd_out);
            ft_putchar_fd('=', cmd->fd_out);
            ft_putstr_fd(env->value, cmd->fd_out);
        }
        curr = curr->next;
    }  
    return (0);
}