/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:04:52 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/01 16:40:54 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exec_cmd(t_cmd *cmd, t_data *data)
{
    int exit_code; 
    if(cmd->is_built_in)
    {
        exit_code = ft_built_ins(cmd, data);
        if(exit_code != -1) //a lo mejor que no devuelva siempre -1 si no mejor ERROR (Ver macros .h)
            ft_exit(); //TO-DO
    }
    //check path 
    if(!cmd->cmd_path)
        ft_error("command not found");

    //cerrar fds 
    ft_close_fds(); // HEREDOC???
    //señales: check creo que esto no es así 
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
    
    //executing
    execve(cmd->cmd_path,cmd->argv ,data->env); // juntar este execve con los ifs de abajo when error management TO-DO

    //errors from execve 
    //TO-DO: return errosrs accordingly !!!
    if(errno == EACCES) //error 126
        return (-1);
    else if(errno == ENOENT) //error 127
        return (-1); 
    else 
        return(-1);
    //return status code 
}


pid_t ft_create_fork(t_cmd *cmd, int fd_in, int fd_out, t_data *data)
{
    pid_t process_id;

    if(fd_in == -1 || fd_out == -1)
        return (-1);
    
    process_id = fork();
    if(process_id == -1)
        return (FORK_ERROR);
    else if(process_id == 0)
    {
        if(dup2(cmd->fd_in, STDIN_FILENO) == -1)
            return (-1);
        if(dup2(cmd->fd_out, STDOUT_FILENO) == -1)
            return (-1);
        ft_exec_cmd(cmd, data);
    }
    return (process_id);
}

int ft_wait_children_process(t_list *cmd_list, t_data *data)
{
    int i;
    int exit_status;
    t_cmd *cmd; 

    i = 0; 
    while(i < data->cmd_nbr)
    {
        cmd = (t_cmd *)cmd_list->content;
        if(cmd->id_process != -1)
            waitpid(cmd->id_process, &exit_status, 0);
        i++;
    }

    cmd = (t_cmd *)ft_lstlast(data->cmds)->content; //duda sobre si este comprueba el cmd_nbr - 1 
    if(cmd->id_process == -1)
        return (1);
    return(ft_return_status(exit_status));
}


// importante current status para cuando haya varios comandos!! para saber si alguno falló anteriormente
int ft_return_status(int status)
{
    int exit_code;
    
    if(WIFEXITED(status))
        return WEXITSTATUS(status);
    if(WIFSIGNALED(status))
    {
        exit_code = WTERMSIG(status); //TO-DO: quit core dumped
        if(exit_code = SIGINT)
            ft_putchar_fd("\n", 1);
        else if(exit_code == SIGQUIT)
            ft_error("Quit (core dumped)"); //Quit (core dumped)
        exit_code = exit_code + 128;
    }
    else  
        exit_code = -1;
    return (exit_code);
}
