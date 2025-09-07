/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:03 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/07 15:01:21 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_multiple_commands(t_cmd *cmd_list, t_data *data)
{
    //rotando por la lista de cmds 
    int exit_status;
    int fds[2];
    t_cmd *cmd;
   // int prev_fd = STDIN_FILENO;

    cmd = cmd_list;
    while(cmd) //TO-DO: sustituir por cmd->next != null o algo asi 
    {
        if(cmd->next)
        {
            if(pipe(fds) == -1)
                ft_error_and_free("pipe error", 1, data);
            if(cmd->fd_out == STDOUT_FILENO) // si no hay redireccion previa
                cmd->fd_out = fds[1];
            else 
                close(fds[1]);

            if(cmd->next->fd_in == STDIN_FILENO)
                cmd->next->fd_in = fds[0];
            else 
                close(fds[0]);
        }

        cmd->id_process = ft_create_fork(cmd,cmd->fd_in,cmd->fd_out,data); //pasarle los fds? 
        
        if(cmd->id_process == FORK_ERROR) //revisar
            ft_error_and_free("fork error", 1, data);
        
        //Cerramos fds
        if (cmd->fd_in != STDIN_FILENO)
            close(cmd->fd_in);
        if (cmd->fd_out != STDOUT_FILENO)
            close(cmd->fd_out);
        
        cmd = cmd->next;
    }
    //to-do lstclear
    
    //wait pids for child process and return status code
    exit_status = ft_wait_children_process(cmd_list);
    return (exit_status);
}

//TO-DO: fix
int ft_single_cmd(t_cmd *cmd, t_data *data)
{
    pid_t pid;
    int exit_status;
    int exit_code; 

    if(cmd->fd_in == -1 || cmd->fd_out == -1)
        return (1);
    
    if(cmd->is_builtin)
    {
        exit_code = ft_built_ins(cmd, data);
        if(exit_code != -1)
            return (exit_code);
    }
    pid = fork();
    if(pid == -1)
        return (FORK_ERROR); //to do:  cortar exe
    else if(pid == 0)
    {
        if(dup2(cmd->fd_in, STDIN_FILENO) == -1)
            ft_error_and_free("dup error", 1, data);
        if(dup2(cmd->fd_out, STDOUT_FILENO) == -1)
            ft_error_and_free("dup error", 1, data);
        ft_exec_cmd(cmd, data);
    }
    waitpid(pid, &exit_status, 0);
    return (ft_return_status(exit_status)); 
}

void ft_executer(t_cmd *cmd_list, t_data *data)
{
    t_cmd *cmd;
    int exit_code;
    
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    
    if(!cmd_list)
        return ;
    
    if(!cmd_list->next)
    {
        cmd = cmd_list;
        exit_code = ft_single_cmd(cmd, data);
    }
    else
        exit_code = ft_multiple_commands(cmd_list, data);
    if(exit_code != -1)
        data->exit_status = exit_code; 

    //liberar la lista de comandos una vez haya acabado !! TO-DO: free memory of cmd_list
    // ft_free_cmd_list(); //TO-DO
}
