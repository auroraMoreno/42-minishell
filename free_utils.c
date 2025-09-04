/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:21:47 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/04 16:14:21 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_free_cmd_list(t_cmd *cmd_list)
{
    t_cmd *tmp;
    int i;

    while (cmd_list)
    {
        tmp = cmd_list->next;

        // liberar argv
        if (cmd_list->argv)
        {
            i = 0;
            while (cmd_list->argv[i])
            {
                free(cmd_list->argv[i]);
                i++;
            }
            free(cmd_list->argv);
        }

        // liberar infile y outfile si existen
        if (cmd_list->infile)
            free(cmd_list->infile);
        if (cmd_list->outfile)
            free(cmd_list->outfile);

        // liberar redirs (si tienes un free específico para redirecciones)
        if (cmd_list->redirs)
            free_redirs(cmd_list->redirs);

        // liberar assignments (si usas NAME=VALUE antes de cmd)
        if (cmd_list->assignments)
            free_assignments(cmd_list->assignments);

        free(cmd_list);
        cmd_list = tmp;
    }
}


void ft_free_all(t_data *data)
{
	//free pwd
	if(data->pwd)
		free(data->pwd);
	//free cmd_list
	if(data->cmd_list)
		ft_free_cmd_list(data->cmd_list);
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