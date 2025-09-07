/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:21:47 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/07 18:29:25 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_all(t_data *data, t_cmd *cmd_list)
{
	if(data->pwd)
		free(data->pwd);
    if(data->cmd_line)
        free(data->cmd_line);
    if(data->cmd_list)
        free_cmds(cmd_list, NULL);
    if(data->env_cpy)
        ft_free_matrix(data->env_cpy);
    free(data);
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
