/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:04:52 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/21 19:29:35 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_wait_child_status()
{
    
}

void ft_exec_cmd(t_cmd *cmd, t_env *env)
{
       //get path cmd
        cmd->cmd_path = get_route(cmd->cmd_name, g_data->env_parsed);
       //execve
       if(execve(cmd->cmd_path,cmd->args, g_data->env_parsed) == -1)
        ft_error("Error executing command."); 
}

void ft_child_process(t_cmd *cmd, int fd_input, int fd_output)
{
    // poner bien los stdin/out para que el proceso lea /escriba por donde le toque
    if(fd_input != STDIN_FILENO)
    {
        // si no es STDIN hacemos dup para que lea del fd_input y no del teclado (stdin)
        //porq necesitamos que stdin lea del fd_input y no del teclado
        //si algo va mal error 
        if(dup2(fd_input, STDIN_FILENO) == -1)
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
    if(cmd->infile || cmd->outfile || cmd->append)
        ft_handle_redir(cmd);

    //checkeamos si hay cmds/args
    if(!cmd->cmd_name || !cmd->cmd_path)
        exit(EXIT_SUCCESS);
    //checkeamos si es un built in
    if(cmd->is_built_in)
        ft_built_ins(cmd, g_data->env);
    //checkeamos si es un cmd normal
    ft_exec_cmd(cmd, g_data->env);
    
}