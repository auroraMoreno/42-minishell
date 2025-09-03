/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:46:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/03 12:39:39 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  to-do exit code 

int ft_heredoc_read_more_content(t_data *data)
{
        int fds[2];
        char *line;
        char *content;
        pid_t process_id;
        int exit_status;
        
       //signals 
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
       //hacer forks BASARSE EN OLD METHOD, pe
        if(pipe(fds) == -1)
            ft_exit();
        process_id = fork();
        if(process_id == 0)
        {
            close(fds[0]); //el hijo solo escribe
            //signals:
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_IGN);

            // ahora tengo que hace el readline
            line = readline(">");
            if(!line)
            {
                close(fds[1]);
                //FREE AND ERROR TO DO
            }
            
            ft_putstr_fd(line, fds[1]);
            close(fds[1]); //ya no hace falta
            //free memory 
            
        }
        else if(process_id == -1)
        {
            close(fds[0]);
            close(fds[1]);
            ft_exit();
        }
        waitpid(process_id, &exit_status, 0);
        content = ft_read_content_heredoc(fds[0]);
        close(fds[0]);
        if(!content)
            ft_exit(); //TO-DO
        //ahora hay que update el heredoc_content
        ft_update_content(content, data);
            
}

int ft_heredoc_write_content(int from_token, char *delimitter, t_data *data)
{
    char **heredoc_content; 

    heredoc_content = data->heredoc_content;
    //leemos el cmd_lines 
    while(heredoc_content[from_token])
    {
        //si encuentra el deimitter => fin bucle
        if(ft_strcmp(heredoc_content[from_token], delimitter))
        {
            //el delimitter estaria en una linea solo 
            //si llego aqui es porq he encontrado el delimitter 
            //pero tengo que gestionar que despues del delimitter no haya algo 
            ft_remove_heredoc_lines(from_token + 1, data);
            if(data->heredoc_fds[1] == -1) //cerramos extremo escritura it's a check para por is ha habido problemas con el fd 
                return ; //TO-DO 
            if(close(data->heredoc_fds[1] == -1))
                ft_error(); //TO-DO
            return (1)
;        }
        else
        {
            ft_putendl_fd(heredoc_content[from_token], data->heredoc_content[1]); //si no tenemos que escribirlo todo (TO-DO EXPAND VAR VALUES ???)
            //TO-DO: error check!! 
        }
        from_token++;
    }    
    return (0);
}


int ft_heredoc(int from_token, char *delimitter, t_data *data)
{
    int exit_status;

    //hasta que encuentra el delimitter (ej:EOF)
    while(1)
    {
        //escribir en el pipe hasta que encuentre el delimitter
        if (ft_heredoc_write_content(from_token, delimitter, data) == 1)
            return (1);
        
        // si no encuentro delimitter abro prompt
        exit_status = ft_heredoc_read_more_content(data);
        //exit status TO-DO HANDLE
        if(exit != 0)
        {
            close(data->heredoc_fds[1]);
            if(exit_status == -1)
                return (0);
            else 
                return (1);
        }
        from_token = 0; //IMPORTANTE VOLVER A EMPEZAR DESDE EL PRINCIPIO POR EL DELIMITTER PARA QUE NO NOS LO PERDAMOS ????

    }
}

/*
cat <<EOF
Hola
linea2
linea3
EOF
*/