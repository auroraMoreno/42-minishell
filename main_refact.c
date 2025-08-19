/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_refact.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 11:57:36 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/19 17:42:23 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
	if(sig == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        g_data->exit_status = 1; //To-Do: handle.
    }
}

void ft_run_shell()
{
    t_cmd *cmd; // aqui de momento solo viene 1 porq quiero probar
    while(1)
    {
        //TO-DO add signals? 
        
        g_data->cmd_line = readline(g_data->prompt);
        if(!g_data->cmd_line) // EOF ERROR
        {
            //free
            //send error:
            ft_error("Exiting..."); //TO-DO: mensaje error 
        }
        add_history(g_data->cmd_line);
        
        //parser / lexer

        //cmd init
        cmd = ft_init_cmd(g_data->cmd_line, g_data->built_ins); //sustituir por init_cmd_list  
        // executer 
        ft_executer(cmd);
        //free 
        if(g_data->cmd_line)
            free(g_data->cmd_line);
            
    }
    
    rl_clear_history();
}

int main(int argc, char **argv, char **env)
{
    //void argc y argv de momento no me hacen falta
    (void)argc;
    (void)argv;
    //hacemos init necesarios:
        //init env

        //init de los built in
        //init data shell: prompt, 
    ft_init_data(env);

    //signals: not sure if they belong here 
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    
    // run shell 
    ft_run_shell();
        // check for EOF error

    //free mem
    ft_free_env(&g_data->env);
    
    return (0);
    

}