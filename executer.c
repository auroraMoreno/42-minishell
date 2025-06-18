/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:03 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/18 09:31:07 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO-DO: mejorar este método 

void ft_execute_cmd(char *cmd, char *flag, t_data data)
{
    printf("%s", cmd);
    if(fork() == 0) // TO-DO: check de errores 
    {
        printf("inside fork");
        execve(cmd, (void *)flag, data.env_parsed);
    }
}

void ft_handle_exe(char *cmd, char *flags, t_built_in_type builtins[], t_data data)
{

    (void)flags;
    // hacer comprobación de si es built_in
    //TO-DO: Hacer comprobacion de nulls y demas y lanzar errors, dentro del bucle tmb 
    int is_built_in = 0;
    int i = 0;
    while(i < 7)
    {
        if(!ft_strncmp(builtins[i].built_in_name, cmd, ft_strlen(cmd)))
        {
            printf("is built in");
            if(!ft_strncmp("env", cmd, ft_strlen(cmd)))
                builtins[i].foo(data.env);      
            else if(!ft_strncmp("export", cmd, ft_strlen(cmd)))
            {
                char *args[] = {"A=\"Valor1\"","B=\"Valor2\"", NULL};
                builtins[i].foo(args , data.env);
            }
            else if(!ft_strncmp("unset", cmd, ft_strlen(cmd)))
            {
                char *args[] = {"A","B", NULL};
                builtins[i].foo(args , data.env);
            }
            else if(!ft_strncmp("cd", cmd, ft_strlen(cmd)))
                builtins[i].foo(NULL, data.env);      
            else   
                builtins[i].foo("hola que tal", NULL); 
            is_built_in = 1;
            break;  
        }
        i++;
    }
    
    if(is_built_in == 0)
    {
        ft_execute_cmd(cmd, flags, data);
        wait(NULL);
    }
}

/*if(cmd.is_built_in)
    // si es built in
    // llamar a la función built in 
else 
    // si no es built in
*/ 