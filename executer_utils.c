/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:04:52 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/04 19:15:34 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void ft_close_fds(t_data *data)
{
    if(data->heredoc_fds[0] == -1 || data->heredoc_fds[1] == -1)
        return; //TO-DO: review este return 
    if(close(data->heredoc_fds[0]) == -1)
        perror("error");
    data->heredoc_fds[0] == -1;
    if(close(data->heredoc_fds[1]) == -1)
        perror("error");
    data->heredoc_fds[1] = -1;
}
*/

void ft_exec_cmd(t_cmd *cmd, t_data *data)
{
    int exit_code; 
    char *path; 
    if(cmd->is_builtin)
    {
        exit_code = ft_built_ins(cmd, data);
        if(exit_code != -1) //a lo mejor que no devuelva siempre -1 si no mejor ERROR (Ver macros .h)
            ft_error_and_free("",exit_code,data); //TO-DO free memory, no es error critico asi que no puedo usar ft_error_and_free 
    }
    //check path 
    if(!cmd->argv[0])
    {
        // TO-DO free mem y lanzar 127

        ft_error_and_free("command not found", 1, data);
        
    }
    //TO-DO REVIEW !!!! 
    //ft_close_fds(data); // HEREDOC???
    // TO-DO: free cmd_list!! ???

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
    

    //executing
    path = get_route(cmd->argv[0], data->env_cpy, data);
    //execve errors: efault, enametoolong
    if(execve(path,cmd->argv, data->env_cpy) == -1)
    {
        //TO-DO: error & free 
        if(errno == EACCES) //error 126 no tiene permisos
            ft_error_and_free("permission denied", 126, data);  
        else if(errno == ENOENT) //error 127 no encuentra
            ft_error_and_free("command not found" ,127, data); 
        else 
            ft_error_and_free("error", 1, data);
    }

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
            ft_error_and_free("dup error", 1, data);       //return (-1);

        if(dup2(cmd->fd_out, STDOUT_FILENO) == -1)
            ft_error_and_free("dup error",1, data);   //return (-1);
        ft_exec_cmd(cmd, data);
    }
    return (process_id);
}


t_cmd *ft_cmd_last(t_cmd *cmd_list)
{
    if (!cmd_list)
        return (NULL);
    while (cmd_list->next)
        cmd_list = cmd_list->next;
    return (cmd_list);
}

int ft_wait_children_process(t_cmd *cmd_list)
{
    // int i;
    int exit_status;
    t_cmd *cmd; 

    cmd = cmd_list;
    // i = 0;
    while(cmd) //TO-DO: sustituir por ->next 
    {
        if(cmd->id_process != -1)
            waitpid(cmd->id_process, &exit_status, 0);
        cmd = cmd->next;
        // i++;
    }

    //cmd = (t_cmd *)ft_lstlast(data->cmds)->content; //duda sobre si este comprueba el cmd_nbr - 1 
    cmd = ft_cmd_last(cmd_list);
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
        exit_code = WTERMSIG(status);
        if(exit_code == SIGINT)
            ft_putchar_fd('\n', 1);
        else if(exit_code == SIGQUIT)
            ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
        exit_code = exit_code + 128;
    }
    else  
        exit_code = -1; // confirmar pq -1 
    return (exit_code);
}
