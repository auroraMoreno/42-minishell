/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:01:23 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/29 00:10:31 by aumoreno         ###   ########.fr       */
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


void ft_handle_redir(t_cmd *cmd)
{

    /** CAMBIAR TODO ESTO CUANDO ACALAREMOS COMO LLEGAN REDIRS 
     *  DE MOMENTO AHORA SOLO UN POCO PSEUDOCODIGO
     * tengo que hacer bucle para que vaya rotando por las redirecciones ??
    */

    //check heredoc
    if(cmd->redir_type == REDIR_IN)
    else if(cmd->redir_type == REDIR_OUT)
    else if(cmd->redir_type == HEREDOC)
        ft_heredoc(); //TO-DO: pasarle el delimitter (no sé cómo me va a llegar aún)
    else if(cmd->redir_type == REDIR_APPEND)
    
    
    //infile redir
    if(cmd->infile)
        ft_handle_in_redir(cmd);
    
    //outfile redir
    if(cmd->outfile)
        ft_handle_out_redir(cmd);
            
}