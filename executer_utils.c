/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:04:52 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/25 18:05:01 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exec_cmd(t_cmd *cmd, t_data *data)
{
    if(cmd->is_built_in)
    {
        data->exit_status = ft_built_ins(cmd, data->env);
        if(data->exit_status != -1)
            ft_exit(); //TO-DO
    }
    //check path 
    if(!cmd->cmd_path)
        ft_error("command not found");

    //cerrar fds 
    ft_close_fds(); // ? 
    //señales: check creo que esto no es así 
    signal(SIGINT, ft_handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    //executing
    execve(cmd->cmd_path,cmd->argv ,data->env);

    //errors from execve 
    //TO-DO: return errosrs accordingly
    if(errno == EACCES)
        return (-1);
    else if(errno == ENOENT)
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
        return (-1);
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
    t_cmd *cmd; 


    i = 0; 
    while(i < data->cmd_nbr)
    {
        cmd = (t_cmd *)cmd_list->content;
        if(cmd->id_process != -1)
            waitpid(cmd->id_process, &data->exit_status, NULL);
        i++;
    }

    return(ft_return_status(data->exit_status));
}


// importante current status para cuando haya varios comandos!! para saber si alguno falló anteriormente
int ft_return_status(int status)
{
    if(WIFEXITED(status))
        g_data->exit_status = WEXITSTATUS(status);
    else if(WIFSIGNALED(status))
        g_data->exit_status = WTERMSIG(status) + 128; //TO-DO: quit core dumped
    else  
        g_data->exit_status = 1;
    if(g_data != 0)
        return ERROR; //CHANGE THIS TO RETURN EXIT STATUS? 
        
    return SUCCESS;
}


void ft_child_process(t_cmd *cmd, int fd_input, int fd_output, t_data *data)
{
    if(fd_input == -1 && fd_output == -1)
        return (-1);
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
    
    //hacemos redir, add heredoc (TO-DO)
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