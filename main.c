/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:02:39 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/26 12:16:11 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
	if(sig == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

int main(int argc, char **argv, char *envp[])
{
    (void)argc; //TO-DO: comprobar que vienen argumentos 
    (void)argv; 
    
    char cwd[PATH_MAX]; // poner en un struct (directory_info ?)
    char *user;         // struct directory info ?
    char *prompt = NULL;
    char *prompt_formatted = NULL;
    char *cmd = NULL;
    // TO_DO: alojar mem ?
    t_built_in_type built_ins[7]; //TO-DO: malloc this ? 
    t_data data; //TO-DO: should this be a pointer ? 
    t_cmd cmd_data;

    
    user = ft_strjoin(getenv("USER"), ":~");
    signal(SIGQUIT, SIG_IGN); // TO-DO: Ctrl D signal doesn't seem to be working properly 
    signal(SIGINT, handle_sigint);
    
    ft_init_builtins(built_ins);

    data.env = ft_init_env(envp); //TO-DO: review 
    data.env_parsed = envp; // TO-DO: review too 
    
    while (1)
    {
        //TO-DO: refact this code 
        if (getcwd(cwd, sizeof(cwd)) != NULL && user != NULL) 
        {
            prompt = ft_strjoin(user, cwd);
            if(!prompt) break;
            // prompt = ft_strjoin(prompt, "$ "); TO-DO: MIRAR ESTO DEL $
            prompt_formatted = ft_strjoin(prompt, " ");
            if(!prompt_formatted) break;
            cmd = readline(prompt_formatted);
        
            if (!cmd || !user || !prompt || !prompt_formatted)
                break;
            add_history(cmd);
            //parser
            
            // execute TO-DO: esto modificarlo cuando parser / syntax este hecho 
            cmd_data = ft_init_cmd(cmd, built_ins); // convertir esto en lista  
            ft_handle_exe(cmd_data, built_ins, data); // le va llegar una lista
            if (prompt) free(prompt);
            if (prompt_formatted) free(prompt_formatted);
            if (cmd) free(cmd);

        }
        else
            printf("didnt work");
        
    }

    rl_clear_history();

    ft_free_env(&data.env); // TO-DO: review 
    
    // TO-DO: review 
    if (user)
        free(user);
    if (prompt)
        free(prompt);
    if(prompt_formatted) 
        free(prompt_formatted);
    if(cmd)
        free(cmd);
    return (0);
}