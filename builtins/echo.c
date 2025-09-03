/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:01:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/26 12:10:10 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_check_n_flag(char *flags)
{
    int i;
    
    if(!flags)
        reutrn (0);

    i = 0;
    while(flags[i])
    {
        if(ft_strncmp(&flags[i], "n", 1) != 0)
            return (0); // porq solo puede haber n    
        i++;
    }
    return (1);
}

int ft_echo(t_cmd *cmd, t_data *data)
{
    char **argv;
    int i;
    int newline;

    newline = 1;
     if(cmd->flags && ft_check_n_flag(cmd->flags))
        newline = 0; 
    
    i = 0;
    while(cmd->args[i])
    {
        ft_putstr_fd(cmd->args[i], cmd->fd_out);
        if(cmd->args[i + 1])
            ft_putchar_fd(' ', cmd->outfile);
        i++;
    }

    if(newline)
        ft_putchar_fd('\n', cmd->fd_out);
    
    return (0);
}
