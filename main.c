/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:02:39 by aumoreno          #+#    #+#             */
/*   Updated: 2025/05/05 18:17:26 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
    // poner un new line 
    

}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    char cwd[PATH_MAX]; // poner en un struct (directory_info ?)
    char *user;         // struct directory info ?
    char *prompt;
    char *prompt_formatted;
    char *cmd;
    
    user = ft_strjoin(getenv("USER"), ":~");
    
    if (getcwd(cwd, sizeof(cwd)) != NULL && user != NULL)
    {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, handle_sigint);
        // TO_DO: alojar mem ?
        while (1)
        {
            prompt = ft_strjoin(user, cwd);
            // prompt = ft_strjoin(prompt, "$ "); TO-DO: MIRAR ESTO DEL $
            prompt_formatted = ft_strjoin(prompt, " ");
            cmd = readline(prompt_formatted);
            
            if (!cmd || !user || !prompt || !prompt_formatted) // por esto no va el ctrl c
                break;
            printf("%s", cmd);
            free(prompt);
            free(prompt_formatted);
            free(cmd);
        }
    }
    else
        printf("didnt work");

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