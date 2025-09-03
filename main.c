/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 11:57:36 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/03 20:31:49 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO-Do: repasar cómo cesar me manda el heredoc y tal 
void ft_run_shell(t_data *data)
{
    int from_token;
    t_cmd *cmd; // aqui de momento solo viene 1 porq quiero probar
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
        { //exit_perror
            //free TO-DO
            //send error:
            ft_error("Exiting..."); //TO-DO: mensaje error 
        }
        add_history(data->cmd_line);
        //PARSER/LEXER  
        
        //cmd init
        cmd = ft_init_cmd(data->cmd_line, data->built_ins); //sustituir por init_cmd_list  
        //heredoc ? depende de como me llegue será un int from_token o un token o algo así 
        if(cmd->heredoc) //TO-DO FLAG HEREDOC hay dos cmd structs 
        {
            //from token es temporal, luego habrá que sustituirlo por el token actual o por lo que sea 
            //pero la logica es que si hay heredoc entonces le pasamos a partir de la siguiente linea 
            // y la procesamos hasta que encuentre el delimitter (ex: EOF)
            // el valor que va a devolver heredoc va a ser un flag que va a indicar si hay que seguir leyendo 
            //despues del heredoc o no, ejemplo:
            /*
            echo hola <<EOF
            linea 1
            linea 2
            EOF
            ls -l
            */
            if(pipe(data->heredoc_fds) == -1)
                ft_exit(); //TO-DO
            ft_heredoc(from_token + 1, delimitter, data); //return flag 
        }
        // executer 
        ft_prepare_executer(cmd, data); //TO-DO: a lo mejor pongo aqui el heredoc 
        //free TO-DO
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
    data = malloc(sizeof(t_data));
    if(!data)
        return (1);
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
    //free mem
    ft_free_all(data); // TO-DO 
    return (data->exit_status); //QUITAR VARIABLE GLOBAL!!
}