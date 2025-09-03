/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:21:47 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/03 18:38:29 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_free_cmd_list(t_list *cmd_list)
{

	
}

void ft_free_all(t_data *data)
{
	//free pwd
	if(data->pwd)
		free(data->pwd);
	//free cmd_list
	if(data->cmds)
		ft_free_cmd_list(data->cmds);
	//free env_cpy
	if(data->env_cpy)
		ft_free_matrix(data->env_cpy);
	//free env
	if(data->env)
		ft_free_env(data->env);
		
}

void	ft_free_env_node(void *content)
{
	t_env *env = (t_env *)content;

	if (!env)
		return;
	
	if(env->key)
		free(env->key);
	if(env->value)
		free(env->value);
	free(env);
}


void ft_free_env(t_list **env_list)
{
   	if (env_list && *env_list)
		ft_lstclear(env_list, ft_free_env_node);
}