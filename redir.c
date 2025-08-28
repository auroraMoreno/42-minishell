/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:01:23 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/28 22:07:43 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TO DO: ADD ERROR HANDLING TO THIS !!! */

void ft_handle_out_redir(t_cmd *cmd)
{
    int fd;
    // handle append too
    if(cmd->append == 1)
        fd = open(cmd->outfile, O_WRONLY, O_CREAT, O_APPEND, 0644); //check si right permissions
    else 
        fd = open(cmd->outfile, O_WRONLY, O_CREAT, O_TRUNC, 0644);
    
    if(fd < 0)
        ft_error("Error opening infile");
    
    if(dup2(fd, STDOUT_FILENO) == -1)
    {
        close(fd);
        ft_error("Error duplicating");
    }
    close(fd);
}

void ft_handle_in_redir(t_cmd *cmd)
{
    int fd;

    fd = open(cmd->infile, O_RDONLY);
    if(fd < 0)
        ft_error("Error opening infile"); //TO-DO: REVISAR MENSJAES DE ERROR
    if(dup2(fd, STDIN_FILENO) == -1)
    {
        close(fd);
        ft_error("Error duplicating");
    }
    close(fd);
}

void ft_handle_redir(t_cmd *cmd)
{

    //check heredoc
    
    
    //infile redir
    if(cmd->infile)
        ft_handle_in_redir(cmd);
    
    //outfile redir
    if(cmd->outfile)
        ft_handle_out_redir(cmd);
            
}