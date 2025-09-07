/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:27:26 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/07 14:16:04 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO-Do: repasar cómo cesar me manda el heredoc y tal 
void ft_run_shell(t_data *data)
{
    //int from_token;

    while(1)
    {
        //TO-DO add signals? 
        signal(SIGINT, ft_handle_sigint);
        signal(SIGQUIT, SIG_IGN);
        
        data->cmd_line = readline(data->prompt); //to-DO, INIT PROMPT BONITO
        if(g_signal != 0)
        {
            data->exit_status = g_signal;
            g_signal = 0;
        }
        if(!data->cmd_line) // EOF ERROR
        { 
            //TO-DO: cambiar esto a funcion de error
            //ft_putendl_fd("exit", STDERR_FILENO); //TO-DO: mensaje error 
            ft_error_and_free("exit", EOF, data);
        }
        add_history(data->cmd_line);
        //LEXER  
        data->cmd_list = parse_input(data->cmd_line);

        if(!data->cmd_list)
        {
            free(data->cmd_line);
            continue;
        }

        /* REDIRECTIONS AND HEREDOC */
        //ft_handle_redirs(cmd_list, data);

        // executer 
        ft_prepare_executer(data->cmd_list, data); //TO-DO: a lo mejor pongo aqui el heredoc 

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
    // run shell 
    ft_run_shell(data);
    //free mem
    ft_free_all(data); 
    return (data->exit_status);
}