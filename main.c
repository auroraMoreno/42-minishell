/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:02:39 by aumoreno          #+#    #+#             */
/*   Updated: 2025/05/17 14:06:45 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*void ft_print_builtins(t_built_in_type builtins[])
{
    if(!builtins)
        printf("Error in built in");
    else 
    {
        int i = 0;
        while(i <= 6)
        {
            printf("%s\n", builtins[i].built_in_name);
            //printf("%s\n", builtins[i].foo);
            i++;
        }
    }
    
}*/

int main(int argc, char **argv)
{
    (void)argc; //TO-DO: comprobar que vienen argumentos 
    (void)argv; 
    
    char cwd[PATH_MAX]; // poner en un struct (directory_info ?)
    char *user;         // struct directory info ?
    char *prompt;
    char *prompt_formatted;
    char *cmd;
    t_built_in_type built_ins[7];
    
    user = ft_strjoin(getenv("USER"), ":~");
    
    if (getcwd(cwd, sizeof(cwd)) != NULL && user != NULL)
    {
        
        ft_init_builtins(built_ins);
        

        signal(SIGQUIT, SIG_IGN);
        // TO_DO: alojar mem ?
        signal(SIGINT, handle_sigint);
        while (1)
        {
            prompt = ft_strjoin(user, cwd);
            // prompt = ft_strjoin(prompt, "$ "); TO-DO: MIRAR ESTO DEL $
            prompt_formatted = ft_strjoin(prompt, " ");
            cmd = readline(prompt_formatted);
    
            if (!cmd || !user || !prompt || !prompt_formatted)
                break;
            add_history(cmd);
           // printf("%s", cmd);

           // execute 
            
           ft_handle_exe(cmd, NULL, built_ins);

           
            free(prompt);
            free(prompt_formatted);
            free(cmd);
        }
    }
    else
        printf("didnt work");

    rl_clear_history();

    //ft_print_builtins(built_ins);

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