/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:03 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/19 16:45:17 by aumoreno         ###   ########.fr       */
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
void ft_handle_exe(t_cmd cmd_data,  t_built_in_type builtins[], t_data data)
{

    // hacer comprobación de si es built_in
    //TO-DO: Hacer comprobacion de nulls y demas y lanzar errors, dentro del bucle tmb 
    //int is_built_in = 0;
    int i = 0;

    //add un if que sea if command is built in para poder quitar var built in 

    //{
        //if(!ft_strncmp(builtins[i].built_in_name, cmd, ft_strlen(cmd)))
        // {
            if(cmd_data.is_built_in == 1)
            {             
                //acabar esto    
                while(i < 7)
                { //TO-DO: modificar esto a que recorra builtins 
                    if(!ft_strcmp("echo", cmd_data.cmd_name))
                        builtins[i].foo("hola que tal", NULL); 
                    else if(!ft_strcmp("cd", cmd_data.cmd_name))
                        builtins[i].foo(NULL, data.env);  
                    else if(!ft_strcmp("pwd", cmd_data.cmd_name))
                        builtins[i].foo(NULL);    
                    else if(!ft_strcmp("export", cmd_data.cmd_name))
                    {
                        char *args[] = {"A=\"Valor1\"","B=\"Valor2\"", NULL};
                        builtins[i].foo(args , data.env);
                    }
                    else if(!ft_strcmp("unset", cmd_data.cmd_name))
                    {
                        char *args[] = {"A","B", NULL};
                        builtins[i].foo(args , data.env);
                    }
                    else if(!ft_strcmp("env", cmd_data.cmd_name))
                        builtins[i].foo(data.env);      
                    else if(!ft_strcmp("exit", cmd_data.cmd_name))
                        builtins[i].foo(1); //Fix esto porq no puede siempre llegarle 1  
                    i++;
                    break;  
                }
    //}
    }
    else
    {
        char *cmd1[] = {cmd_data.cmd_name, NULL};
        ft_execute_cmd(cmd_data.cmd_path, cmd1, data);
        wait(NULL);
    }
}
