/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:21:47 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/02 12:37:44 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env_node(void *content)
{
	t_env *env = (t_env *)content;

	if (!env)
		return;

	free(env->key);   // only if they were malloc'd!
	free(env->value); // only if they were malloc'd!
	free(env);
}
void ft_free_env(t_list **env_list)
{
   	if (env_list && *env_list)
		ft_lstclear(env_list, ft_free_env_node);
}