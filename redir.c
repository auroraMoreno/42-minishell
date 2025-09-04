/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:01:23 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/04 10:57:28 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TO DO: ADD ERROR HANDLING TO THIS !!! */

int ft_handle_out_redir(t_cmd *cmd)
{
    int fd;
    // handle append too
    if(cmd->append == 1)
        fd = open(cmd->outfile, O_APPEND | O_WRONLY); //check si right permissions
    else 
        fd = open(cmd->outfile, O_TRUNC | O_WRONLY);
    
    if(fd < 0)
    {
        ft_error("Error opening infile");
        close(fd);
        //TO-DO FREE MEMORY 
        
        //no sé que es el num que le llega ahora miramos 

        //exit(EXIT_FAILURE); //fix this para que devuelva bien

        
        return (-1);
    }
    
    if(dup2(fd, STDOUT_FILENO) == -1)
    {
        close(fd);
        ft_error("Error duplicating");
        //liberar memoria 
        return (-1);
    }
    close(fd);
    return (fd);
}

void ft_handle_in_redir(t_cmd *cmd)
{
    int fd;

    fd = open(cmd->infile, O_RDONLY);
    if(fd < 0 || (cmd->redir_type == REDIR_IN && access(cmd->infile, R_OK) != 0))
    {
        ft_error("Error opening infile"); //TO-DO: REVISAR MENSJAES DE ERROR
        //hacer free memory
        return (0);
    }
    if(dup2(fd, STDIN_FILENO) == -1)
    {
        close(fd);
        ft_error("Error duplicating");
    }
    close(fd);
    return (fd);
}


void ft_handle_redir(t_cmd *cmd_list, t_data *data)
{
    //recorrer la lista de cmd_list 
    // ir mirando que tipo de redir tiene cada cmd si esq hay redir
    //llamar a los métodos adecuados           
    t_cmd *cmd;
    t_redir *redirs;
    
    cmd = cmd_list;
    
    while(cmd)
    {
        cmd->fd_in = STDIN_FILENO;
        cmd->fd_out = STDOUT_FILENO;

        redirs = cmd->redirs;
        
        while(redirs)
        {
            
        }
    }
}