/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:23 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/04 18:15:50 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(t_cmd *cmd, t_data *data)
{
    char *cwd;
    
    cwd = getcwd(NULL, 0);
    if(!cwd)
        return(ft_formatted_error("current working directory not found", "pwd", data));
    
    ft_putendl_fd(cwd, cmd->fd_out);
    free(cwd);
    return (0);
}