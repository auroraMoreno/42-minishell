/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:04:52 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/19 11:37:49 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_child_process(t_cmd *cmd, int fd_input, int fd_output)
{
    // poner bien los stdin/out para que el proceso lea /escriba por donde le toque
    if(fd_input != STDIN_FILENO)
    {
        // si no es STDIN hacemos dup para que lea del fd_input y no del teclado (stdin)
        //porq necesitamos que stdin lea del fd_input y no del teclado
        //si algo va mal error 
        if(dup2(fd_input, STDERR_FILENO) == -1)
            ft_error("Error dup2");
        close(fd_input);
    }
    if(fd_output != STDOUT_FILENO)
    {
        //misma lógica pero para stdout
        if(dup2(fd_output, STDOUT_FILENO) == -1)
            ft_error("Error dup2"); 
        close(fd_output);
    }
    
    //hacemos redir
    if(cmd->redir)
        ft_handle_redir();

    //checkeamos si hay cmds/args

    //checkeamos si es un built in

    //checkeamos si es un cmd normal

    //exit para finalizar el proceso hijo 
}