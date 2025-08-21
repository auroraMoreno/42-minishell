/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:03 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/21 18:31:29 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void ft_execute_cmd(char *cmd_path, char **flag, t_data data)
{
    if(fork() == 0) // TO-DO: check de errores 
    {
        if(execve(cmd_path, flag, data.env_parsed) < 0)
            ft_error("error en execve");
    }
}*/

//fork 
void ft_single_cmd(t_cmd *cmd, int fd, t_list *env)
{
    pid_t pid;
    int status; 
    int fds[2];
    
    pid = fork();
    if(pid == -1)
        ft_error("error in fork");
    if(pid = 0)
        ft_child_process(cmd, fd, STDOUT_FILENO); // aunq solo hay un comando pero para redir (TO-DO)
    if(fd != STDIN_FILENO) //cerramos esto we dont needed anymore solo para conectar este cmd con el anterior
        close(fd);
    
    status = ft_wait_child_status();
    if(status == ERROR)
        return (ERROR);
    
    return (SUCCESS);
}

// recursivad, volvemos a llamar a este metodo 
// return status
void ft_executer(t_cmd *cmd, int fd_input, t_list *env)
{
    
    //check si cmd not nul
    if(!cmd)
        return ; //TO-DO: check errores 
    //checkeamos si es un built in
    if(cmd->is_built_in)
        ft_built_ins(cmd, env);
    
    if(!cmd->next)
        ft_single_cmd(cmd, fd_input, env);
    //cuando haya mas haremos un check de que si no hay next, simple cmd exe
    
    //si hay next => fork y pipe
    if(cmd->next)
        ft_create_pipe_fork() ;
    // checkeamos pid para child process
    
    // cerramos fds 
    
    // recursividad, volvemos a llamar a exe hasta que no haya mas cmd nexts
    ft_execute_cmds(cmd, STDIN_FILENO, env);
    //hacemos los waits 
    ft_wait(); // ??
}

//TO-DO: mejorar este método 
// el primer param de aqui va a ser una lista de cmd 
// TO-DO: expander, add heredocs, process comands 
void ft_prepare_executer(t_cmd *cmd_data)
{

    // hacer comprobación de si es built_in
    //TO-DO: Hacer comprobacion de nulls y demas y lanzar errors, dentro del bucle tmb 
    //rodear esto con un bucle porq no va llegar solo un cmd_data \
    // si rodeo todo con un bucle hasta que ya no haya comandos 

    ft_expand(); //TO-DO
    
    ft_heredocs(); //TO-DO

    //le llegará los cmd procesados con sus herdocs y expanders 
    //considerar no pasarle el g_data porq es global jeje 
    ft_executer(cmd_data, STDIN_FILENO, g_data->env); // de momento solo uno habrá pasarle lista
    
}
