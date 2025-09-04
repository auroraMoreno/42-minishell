/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:01:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/04 13:48:25 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_check_n_flag(char *flags)
{
    int i;
    
    if(!flags || flags[0] != '-')
        return (0);

    i = 1;
    while(flags[i])
    {
        if(ft_strncmp(&flags[i], "n", 1) != 0)
            return (0); // porq solo puede haber n    
        i++;
    }
    return (1);
}

int ft_echo(t_cmd *cmd)
{
    //char **argv;
    int i;
    int newline;

    i = 1;
    newline = 1;
     if(cmd->argv[i] && ft_check_n_flag(cmd->argv[i]))
     {
        newline = 0; 
        i++;
     }
    
    //TO-DO modificar esto porq no hay pprop args, está todo en argv
    while(cmd->argv[i])
    {
        ft_putstr_fd(cmd->argv[i], cmd->fd_out);
        if(cmd->argv[i + 1])
            ft_putchar_fd(' ', cmd->fd_out);
        i++;
    }

    if(newline)
        ft_putchar_fd('\n', cmd->fd_out);
    
    return (0);
}
