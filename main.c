/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 11:57:36 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/26 16:50:55 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_run_shell(t_data *data)
{
    t_cmd *cmd; // aqui de momento solo viene 1 porq quiero probar
    while(1)
    {
        //TO-DO add signals? 
        
        data->cmd_line = readline(data->prompt);
        if(!data->cmd_line) // EOF ERROR
        {
            //free
            //send error:
            ft_error("Exiting..."); //TO-DO: mensaje error 
        }
        add_history(data->cmd_line);
        
        //parser / lexer

        //cmd init
        cmd = ft_init_cmd(data->cmd_line, data->built_ins); //sustituir por init_cmd_list  
        // executer 
        ft_prepare_executer(cmd, data);
        //free 
        if(data->cmd_line)
            free(data->cmd_line);
            
    }
    
    rl_clear_history();
}

int main(int argc, char **argv, char **env)
{
    //void argc y argv de momento no me hacen falta
    (void)argc;
    (void)argv;

    t_data *data; // TO-DO: malloc 
    
    //hacemos init necesarios:
        //init env

        //init de los built in
        //init data shell: prompt, 
    ft_init_data(data, env);

    //signals: not sure if they belong here 
    signal(SIGINT, ft_handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    
    // run shell 
    ft_run_shell(data);
        // check for EOF error

    //free mem
    ft_free_env(data->env);
    ft_free_all(); // TO-DO 

    
    return (data->exit_status); //QUITAR VARIABLE GLOBAL!!
    

}