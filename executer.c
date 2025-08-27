/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:03 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/27 20:04:43 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_multiple_commands(t_list *cmd_list, t_data *data)
{
    //rotando por la lista de cmds 
    int i;
    t_cmd *cmd;

    i = 0;
    while(i < data->cmd_nbr)
    {
        cmd = (t_cmd *)cmd_list->content;
        cmd->id_process = ft_create_fork(cmd,cmd->fd_in,cmd->fd_out,data); //pasarle los fds? 
        cmd = cmd_list->next;
        i++;
    }
    //wait pids for child process and return status code
    data->exit_status = ft_wait_children_process(cmd, data);
    return (data->exit_status);
}

//TO-DO: fix
int ft_single_cmd(t_cmd *cmd, int fd, t_data *data)
{
    pid_t pid;
    int exit_status;
    int exit_code; 

    if(cmd->is_built_in)
    {
        exit_status = ft_built_ins(cmd, data);
        if(exit_status != -1)
            return (exit_status);
    }
        
    if(cmd->fd_in == -1 || cmd->fd_out == -1)
        return (-1);
    
    pid = fork();
    if(pid == -1)
        return (-1);
    else if(pid == 0)
    {
        if(dup2(cmd->fd_in, STDIN_FILENO) == -1)
            return (-1); // TO-DO: fix this para que devueva el valor adecuado
        if(dup2(cmd->fd_out, STDOUT_FILENO) == -1)
            return (-1);
        ft_exec_cmd(cmd, data);
    }
    waitpid(pid, &exit_status, 0);
    return (ft_return_status(data, exit_code)); 
}

// recursivad, volvemos a llamar a este metodo 
// return status
void ft_executer(t_list *cmd_list, t_data *data)
{
    int fds[2];
    pid_t pid;
    t_cmd *cmd;
    
    /*signal handling*/
    
    //check si cmd not nul
    if(!cmd_list)
        return ; //TO-DO: check errores 
    
    if(!cmd->next)
    {
        // al ser single command sólo va a tener 1 
        cmd = (t_cmd *)cmd_list->content;
        data->exit_status = ft_single_cmd(cmd, cmd->fd_in, data); //TO-DO: fix, esto no siempre es el status code
    }
    else
        data->exit_status = ft_multiple_commands(cmd_list, data);

    //liberar la lista de comandos una vez haya acabado 
    
}

//TO-DO: mejorar este método 
// el primer param de aqui va a ser una lista de cmd 
// TO-DO: expander, add heredocs, process comands 
void ft_prepare_executer(t_list *cmd_data, t_data *data)
{

    // hacer comprobación de si es built_in
    //TO-DO: Hacer comprobacion de nulls y demas y lanzar errors, dentro del bucle tmb 
    //rodear esto con un bucle porq no va llegar solo un cmd_data \
    // si rodeo todo con un bucle hasta que ya no haya comandos 

    ft_expand(); //TO-DO
    
    ft_heredocs(); //TO-DO

    //le llegará los cmd procesados con sus herdocs y expanders 
    //considerar no pasarle el g_data porq es global jeje 
    ft_executer(cmd_data, data); // de momento solo uno; habrá pasarle lista
    
}
