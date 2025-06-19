/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:03 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/19 11:22:42 by aumoreno         ###   ########.fr       */
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
void ft_handle_exe(char *cmd, char *flags, t_built_in_type builtins[], t_data data)
{

    (void)flags;
    // hacer comprobación de si es built_in
    //TO-DO: Hacer comprobacion de nulls y demas y lanzar errors, dentro del bucle tmb 
    int is_built_in = 0;
    int i = 0;

    //add un if que sea if command is built in para poder quitar var built in 

    while(i < 7) //TO-DO: modificar esto a que recorra builtins 
    {
        if(!ft_strncmp(builtins[i].built_in_name, cmd, ft_strlen(cmd)))
        {
                        
            if(!ft_strcmp("echo", cmd))
                builtins[i].foo("hola que tal", NULL); 
            else if(!ft_strcmp("cd", cmd))
                builtins[i].foo(NULL, data.env);  
            else if(!ft_strcmp("pwd", cmd))
                builtins[i].foo(NULL);    
            else if(!ft_strcmp("export", cmd))
            {
                char *args[] = {"A=\"Valor1\"","B=\"Valor2\"", NULL};
                builtins[i].foo(args , data.env);
            }
            else if(!ft_strcmp("unset", cmd))
            {
                char *args[] = {"A","B", NULL};
                builtins[i].foo(args , data.env);
            }
            else if(!ft_strcmp("env", cmd))
                builtins[i].foo(data.env);      
            else if(!ft_strcmp("exit", cmd))
                builtins[i].foo(1); //Fix esto porq no puede siempre llegarle 1  
            is_built_in = 1;
            break;  
        }
        i++;
    }
    
    if(is_built_in == 0)
    {
        char *cmd1[] = {"ls", NULL};
        ft_execute_cmd("/usr/bin/ls", cmd1, data);
        wait(NULL);
    }
}
