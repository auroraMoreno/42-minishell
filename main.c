/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:02:39 by aumoreno          #+#    #+#             */
/*   Updated: 2025/05/02 14:14:59 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    char cwd[PATH_MAX]; // poner en un struct (directory_info ?)
    char *user; // struct directory info ? 
    user = getenv("USER");
    if(getcwd(cwd, sizeof(cwd)) != NULL && user != NULL)
    { 
        // esto concat y pasarlo a readline y hacer el bucle 
        // faltaria tmb add lo de CTRL + D finaliza y ver lo de CTRL + C 
        // tmb gestionar leaks y alojar mem 
        printf("%s\n", user);
        printf("%s\n", cwd);
    }
    else
        printf("didnt work");

    /*
    while(*env)
    {
        printf("%s\n", *env);
        env++;
    }
    */
    return (0);
}