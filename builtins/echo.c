/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:01:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/03 20:56:51 by aumoreno         ###   ########.fr       */
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
     if(cmd->argv[1] && ft_check_n_flag(cmd->argv[1]))
        newline = 0; 
    
    //TO-DO modificar esto porq no hay pprop args, está todo en argv
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
