/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:42:05 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/03 11:20:22 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_init_env(char **envp) // El problema está aquí 
{
    int i;
    t_list *first;
    t_list *new;
    char **env_cpy;

    env_cpy = ft_cpy_env(envp);

    i = 0;
    while(env_cpy[i])
    {
        new = ft_process_env_values(env_cpy[i]);
        if(!new)
            return (0);
        // add  la lista
        ft_lstadd_back(&first, new);
        i++;
    }
    
    //free envp_cpy: TO-DO (reusar para env_cpy)
    free(env_cpy); //TO-DO

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

int	ft_get_env_size(char **env)
{
	int	len;

	len = 0;
	while (*env)
	{
		len++;
		env++;
	}
	return (len);
}

char **ft_cpy_env(char **env)
{
    int i;
    int env_size;
    char **env_cpy;

    if(!env)
        return;
    env_size = ft_get_env_size(env);
    env_cpy = ft_calloc(env_size + 1, sizeof(char *));
    if(!env_cpy)
        return (0);
    i = 0; 
    while(env[i])
    {
        env_cpy[i] = ft_strdup(env[i]); 
        if(!env_cpy[i])
        {
            free_matrix(env_cpy);
            return (0);
        }
        i++;
    }
    
    env_cpy[i] = '\0';
    return (env_cpy);
}

void ft_init_data(t_data *data, char **env)
{
    signal(SIGINT, SIG_IGN);
    signals(SIGQUIT, SIG_IGN);
    g_signal = 0;
    data->env = ft_init_env(env); //TO-DO: check para mem leaks 
    if(!data->env)
    return (0);
    data->env_cpy = ft_cpy_env(env); //TO-DO: free memory
    // considerar poner aquí los built_ins 
    ft_init_builtins(data);
    data->prompt = "shellprompt"; //TO-DO: formatear esto
    data->cmd_line = NULL;
    data->pwd = getcwd(NULL, 0); //TO-DO: FREE MEMORY
    data->exit_status = 0;
    data->cmds = NULL;
    data->cmd_nbr = 0;
    data->heredoc_content = NULL;
    //TO-DO: review
    data->heredoc_fds[0] = -1;
    data->heredoc_fds[1] = -1; 
}