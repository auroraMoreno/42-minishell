/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:02:39 by aumoreno          #+#    #+#             */
/*   Updated: 2025/05/13 15:38:27 by aumoreno         ###   ########.fr       */
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
            printf("%s", cmd);
            free(prompt);
            free(prompt_formatted);
            free(cmd);
        }
    }
    else
        printf("didnt work");

    rl_clear_history();

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