/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:02:39 by aumoreno          #+#    #+#             */
/*   Updated: 2025/05/02 16:43:20 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    char cwd[PATH_MAX]; // poner en un struct (directory_info ?)
    char *user; // struct directory info ? 
    char *prompt;
    char *add_space;
    char *cmd;
    user = ft_strjoin(getenv("USER"), ":~");
    if(getcwd(cwd, sizeof(cwd)) != NULL && user != NULL)
    { 
        // esto concat y pasarlo a readline y hacer el bucle 
        // faltaria tmb add lo de CTRL + D finaliza y ver lo de CTRL + C 
        // tmb gestionar leaks y alojar mem 
        prompt = ft_strjoin(user, cwd);
        //prompt = ft_strjoin(prompt, "$ "); TO-DO: MIRAR ESTO DEL $ 
        add_space = ft_strjoin(prompt, " ");
        
        while(1)
        {
            cmd = readline(add_space); // de esta forma, no estoy cogiendo aun el cwd cada vez TO-DO 
            printf("%s\n", cmd); 

            if(!cmd)
                break;
            
            free(cmd);
        }
        
    }
    else
        printf("didnt work"); 
   free(user);
   free(prompt);
   free(add_space);
   free(cmd);
   return (0);
}