/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:03 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/25 12:04:11 by aumoreno         ###   ########.fr       */
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
        cmd->id_process = ft_create_fork();

        i++;
    }
}

int ft_single_cmd(t_cmd *cmd, int fd, t_data *data)
{
    pid_t pid;
    int exit_status;

    //checkeamos si es un built in
    if(cmd->is_built_in)
        ft_built_ins(cmd, data->env);
    
    pid = fork(); 
    if(pid == -1)
        ft_error("error in fork");
    // todo tiene que ser un hijo menos los built ins porq si no cerramos la minishell 
    if(pid = 0)
        ft_child_process(cmd, fd, STDOUT_FILENO); // aunq solo hay un comando pero para redir (TO-DO)
    if(fd != STDIN_FILENO) //cerramos esto we dont needed anymore solo para conectar este cmd con el anterior
        close(fd);
    
    signal(SIGINT, SIG_IGN); // para que sue muera el hijo no la shell

    waitpid(pid, &status, 0);

    signal(SIGINT, handle_sigint);
    
    return (ft_return_status(status)); //esto por defecto siempre success
}

// recursivad, volvemos a llamar a este metodo 
// return status
void ft_executer(t_cmd *cmd, t_data *data)
{
    int fds[2];
    pid_t pid;
    
    
    
    //check si cmd not nul
    if(!cmd)
        return ; //TO-DO: check errores 
    
    if(!cmd->next)
        data->exit_status = ft_single_cmd(cmd, ,data);
    else
        ft_multiple_commands(cmd, data);
    
    // checkeamos pid para child process
    if(pid == 0)
    {
        close(fds[0]); //cerramos el fd de lectura hijo no va leer de aqui, 
        //llamamos al child proecess;
        ft_child_process(cmd, fd_input, fds[1]);
    }
    // cerramos fds 
    if(fd_input != STDIN_FILENO) //la ha pasado al hijo ya no hace falta, la cerramos 
        close(fd_input);
    close(fds[1]); //cerramos para que el padre no escriba en el recien creado (lo hace el hijo)
    // recursividad, volvemos a llamar a exe hasta que no haya mas cmd nexts
    ft_executer(cmd, STDIN_FILENO, data->env); //should return ? 
    //hacemos los waits 
    ft_wait(); // ??
}

//TO-DO: mejorar este método 
// el primer param de aqui va a ser una lista de cmd 
// TO-DO: expander, add heredocs, process comands 
void ft_prepare_executer(t_cmd *cmd_data, t_data *data)
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
