/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:27:26 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/07 14:59:58 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_run_shell(t_data *data)
{
    while(1)
    {
        signal(SIGINT, ft_handle_sigint);
        signal(SIGQUIT, SIG_IGN);
        
        data->cmd_line = readline(data->prompt);
        if(g_signal != 0)
        {
            data->exit_status = g_signal;
            g_signal = 0;
        }
        if(!data->cmd_line)
            ft_error_and_free("exit", data->exit_status, data);
        add_history(data->cmd_line);
        //LEXER  
        data->cmd_list = parse_input(data->cmd_line);

        if(!data->cmd_list)
        {
            free(data->cmd_line);
            continue;
        }
        // executer 
        ft_executer(data->cmd_list, data); 

        //TO-DO: free memory
        //ft_free_cmds();
        //free TO-DO
        if(data->cmd_line)
            free(data->cmd_line);
    }
    
    rl_clear_history();
}

int main(int argc, char **argv, char **env)
{
    t_data *data;
    (void)argc;
    (void)argv;

    data = malloc(sizeof(t_data));
    if(!data)
        return (1);
    ft_init_data(data, env);
    signal(SIGINT, ft_handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    ft_run_shell(data);
    ft_free_all(data); 
    return (data->exit_status);
}