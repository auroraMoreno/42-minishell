/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:48 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/06 21:19:04 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long ft_atoi_exit_code(char *str_code)
{
    int i;
    int sign;
    unsigned long res; //check de buffer overflow? 
    
    res = 0;
    sign = 1;
    i = 0;

    while(str_code[i] == 32 || (str_code[i] >= 9 &&  str_code[i] <= 13))
        i++;
    
    if(str_code[i] == '-' || str_code[i] == '+')
    {
        if(str_code[i] == '-')
            sign = -1;
        i++;
    }
    
    while(str_code[i] >= 48 && str_code[i] <= 57)
    {
        res = res * 10 + (str_code[i] - 48);
        i++;
    }
    
    return((long)res * sign % 256);

}

/*
 Exit the shell, returning a status of n to the shell’s parent. If n is omitted, the
 exit status is that of the last command executed. Any trap on EXIT is executed
 before the shell terminates.*/
int ft_exit(t_cmd *cmd, t_data *data)
{ 
    int exit_code;
    
    //si viene más de un argumento entonces too many arguments
    if(cmd->argv[2])
    {
        return(ft_formatted_error("too many arguments", "-bash: exit ", data));
    }
    //si solo viene exit entonces exit normal
    if(cmd->argv[1] == NULL)
    {
        exit_code = data->exit_status;
        ft_free_all(data); //TO-DO
        exit(exit_code);
    }
    //si viene un argumento entonces hacemos el parseo 
    exit_code = ft_atoi_exit_code(cmd->argv[1]);
    // not sure
    if(exit_code == -1)
    {
        //printf("%d\n", exit_code);
        ft_formatted_error("invalid argument", "-bash: exit", data);
        ft_free_all(data); //TO-DO
    }
    // y si no, todo bien hacemos exit normal 
    ft_free_all(data);    
    exit(exit_code);
    
    return (0);
}