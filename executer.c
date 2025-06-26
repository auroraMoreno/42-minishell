/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:03 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/26 12:14:54 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execute_cmd(char *cmd_path, char **flag, t_data data)
{
    if(fork() == 0) // TO-DO: check de errores 
    {
        if(execve(cmd_path, flag, data.env_parsed) < 0)
            ft_error("error en execve");
    }
}

//TO-DO: mejorar este método 
// el primer param de aqui va a ser una lista de cmd 
void ft_handle_exe(t_cmd cmd_data,  t_built_in_type builtins[], t_data data)
{

    // hacer comprobación de si es built_in
    //TO-DO: Hacer comprobacion de nulls y demas y lanzar errors, dentro del bucle tmb 
    //rodear esto con un bucle porq no va llegar solo un cmd_data \
    // si rodeo todo con un bucle hasta que ya no haya comandos 

    t_pipe *piped;

    if(cmd_data.is_built_in == 1)
    {             
        // TO DO: hacer una funcion handle built in 
        //acabar esto    
             //TO-DO: modificar esto a que recorra builtins 
            if(!ft_strcmp("echo", cmd_data.cmd_name))
                builtins[0].foo("hola que tal", NULL); 
            else if(!ft_strcmp("cd", cmd_data.cmd_name))
                builtins[1].foo(NULL, data.env);  
            else if(!ft_strcmp("pwd", cmd_data.cmd_name))
                builtins[2].foo();  
            else if(!ft_strcmp("export", cmd_data.cmd_name))
            {
                char *args[] = {"A=\"Valor1\"","B=\"Valor2\"", NULL};
                builtins[3].foo(args , data.env);
            }
            else if(!ft_strcmp("unset", cmd_data.cmd_name))
            {
                char *args[] = {"A","B", NULL};
                builtins[4].foo(args , data.env);
            }
            else if(!ft_strcmp("env", cmd_data.cmd_name))
                builtins[5].foo(data.env);      
            else if(!ft_strcmp("exit", cmd_data.cmd_name))
                builtins[6].foo(1); //Fix esto porq no puede siempre llegarle 1  
    }
    else
    {
        // si hay un next entonces llamamos al pipex 

        //si no hay un next llamar al metodo de ejecutar normal 
        char *cmd1[] = {cmd_data.cmd_name, NULL};

        //hacer metodo open infile y open outfile (de momento localizado en init pipe)
        if(cmd_data->next) // To Do : Implemententar esto
        {
            ft_init_pipe(piped, cmd_data, data);
            pipex(piped);
        } 
        else
            ft_execute_cmd(cmd_data.cmd_path, cmd1, data); //To-Do si es null el path check
        wait(NULL);
    }
}
