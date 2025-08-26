/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:42:05 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/26 16:45:39 by aumoreno         ###   ########.fr       */
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

//TO-DO: review mejor forma de hacer init de built ins ?
void ft_init_builtins(t_data *data)
{
    //echo
    data->built_ins[0] = "echo";
    //cd
    data->built_ins[1]= "cd";
    //pwd
    data->built_ins[2] = "pwd";
    //export
    data->built_ins[3] = "export";
    //unset
    data->built_ins[4] = "unset";
    //env
    data->built_ins[5] = "env";
    //exit
    data->built_ins[6] = "exit";
}

void ft_init_data(t_data *data, char **env)
{
    data->prompt = "shellprompt"; //TO-DO: formatear esto
    data->cmd_line = NULL;
    data->env = ft_init_env(env); //TO-DO: check para mem leaks 
    data->env_cpy = ft_cpy_env(env);
    // considerar poner aquí los built_ins 
    ft_init_builtins(data);
    data->pwd = getcwd(NULL, 0); //TO-DO: FREE MEMORY
    data->exit_status = 0;
}