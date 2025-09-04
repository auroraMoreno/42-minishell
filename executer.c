/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:03 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/04 19:26:03 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_multiple_commands(t_cmd *cmd_list, t_data *data)
{
    //rotando por la lista de cmds 
    int exit_status;
    t_cmd *cmd;

    cmd = cmd_list;
    while(cmd) //TO-DO: sustituir por cmd->next != null o algo asi 
    {
        // PASAR AQUI EL MÉTODO CREATE FORK !!! 
        cmd->id_process = ft_create_fork(cmd,cmd->fd_in,cmd->fd_out,data); //pasarle los fds? 
        if(cmd->id_process == FORK_ERROR) //revisar
            ft_error_and_free("fork error", 1, data);
        cmd = cmd->next;
    }

    //to-do lstclear
    
    //wait pids for child process and return status code
    exit_status = ft_wait_children_process(cmd);
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

// recursivad, volvemos a llamar a este metodo 
// return status
void ft_executer(t_cmd *cmd_list, t_data *data)
{
    t_cmd *cmd; //esto va a ir recorriendo cmd_list
    int exit_code;
    
    /*signal handling*/
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    
    //check si cmd not nul
    if(!cmd_list)
        return ; //TO-DO: check errores 
    
    if(!cmd_list->next)
    {
        // al ser single command sólo va a tener 1 
        cmd = cmd_list;
        exit_code = ft_single_cmd(cmd, data);
        // solo modificamos el exit status si ft_single_cmd ha ejecutado un comando
        // si hay cualquier otro error no lo cambiamos 
    }
    else
        exit_code = ft_multiple_commands(cmd_list, data);
    //
    if(exit_code != -1)
        data->exit_status = exit_code; 

    //liberar la lista de comandos una vez haya acabado !! TO-DO: free memory of cmd_list
    // ft_free_cmd_list(); //TO-DO
}

//TO-DO: mejorar este método 
// el primer param de aqui va a ser una lista de cmd 
// TO-DO: expander, add heredocs, process comands 
void ft_prepare_executer(t_cmd *cmd_list, t_data *data)
{

    // hacer comprobación de si es built_in
    //TO-DO: Hacer comprobacion de nulls y demas y lanzar errors, dentro del bucle tmb 
    //rodear esto con un bucle porq no va llegar solo un cmd_data 
    // si rodeo todo con un bucle hasta que ya no haya comandos 
    
    //ft_handle_redir(); //preguntar a cesar porq necesito saber cómo me va llegar esa redireccion para poder
    //hacer el switch en handle redir que dependiendo de que redireccion sea llamar a heredoc, append, infile o outfile 

    //le llegará los cmd procesados con sus herdocs y expanders 
    //considerar no pasarle el g_data porq es global jeje 
    ft_executer(cmd_list, data); // de momento solo uno; habrá pasarle lista
    
}
