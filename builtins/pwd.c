/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:23 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/26 00:06:04 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(t_data *data, t_cmd *cmd)
{
    char *cwd;
    
    cwd = getcwd(NULL, 0);
    if(!cwd)
        return(ft_formatted_error("current working directory not found", "pwd", data));
    
    ft_putstr_fd(cwd, cmd->fd_out); // por si pwd > salida.txt 
    free(cwd);
    return (0);
}