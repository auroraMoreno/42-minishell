/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:42:05 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/15 12:02:04 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void ft_init_builtins()
{
    //echo
    g_data->built_ins[0] = "echo";
    //cd
    g_data->built_ins[1]= "cd";
    //pwd
    g_data->built_ins[2] = "pwd";
    //export
    g_data->built_ins[3] = "export";
    //unset
    g_data->built_ins[4] = "unset";
    //env
    g_data->built_ins[5] = "env";
    //exit
    g_data->built_ins[6] = "exit";
}

void ft_init_data(char **env)
{
    g_data->prompt = "shellprompt"; //TO-DO: formatear esto
    g_data->cmd_line = NULL;
    g_data->env = ft_init_env(env); //TO-DO: check para mem leaks 
    g_data->env_parsed = env;
    // considerar poner aquí los built_ins 
    ft_init_builtins();
    getcwd(g_data->pwd, sizeof(g_data->pwd)); //TO-DO: error check? 
    g_data->exit_status = 0;
    
}