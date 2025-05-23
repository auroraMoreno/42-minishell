/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:09:08 by aumoreno          #+#    #+#             */
/*   Updated: 2025/05/23 16:24:55 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    recibe lo que hay que escribir 
        // si !str => \n 
    si tiene flags => 
        //comprobar que la flag es -n 
            si no es -n => print lo que viene 
            si es -n => printf sin \n 
                si viene con -n pero !str , no pinta,¡mos nada
            si no hay flags => printf con \n 
        
*/
int ft_echo(char *str, char *flags)
{
    // sin -n
    if(flags)
    {
       if(str)
            // TO-Do: ver como gestiona esto los numeros, habrá que hacer itoa y decimales y con /
            printf("%s", str);
    }
    // con -n
    else 
    {
        if(!str)
            printf("\n");
        else
            printf("%s\n",str);
    }
    return (0);
}

int ft_cd(char *path)
{
    (void)path;
    printf("Este es el built in cd\n");
    //comprobar que el path es válido
   // if(chdir(path) < 0)
        // TO-DO: hacer una funcion que le pasamos el errno y nos da un error
        //ft_cd_errors(errno);
       // return (0);
    //comprobar que tenemos acceso a ese path

    // cambiar el directrio: chdir ?
    
    chdir(".."); //cambia el path pero no cambia el prompt user
    
    return (0);
}

int ft_pwd()
{
    char cwd[PATH_MAX];

    getcwd(cwd, sizeof(cwd));

    printf("%s\n", cwd);
    
    return (0);
}

int ft_export(char **var_name, char *env[])
{
    //solo el name porq el value se supone que ya está 
    // segun el comportamiento de export si la var a exportar no existe, lista las variables exportadass
    int i; 
    if(!var_name)//list 
    {
      i = 0;
      while(env[i])
      {
        printf("declare -x %s\n",env[i]); // TO-DO: arregalar que el valor esté surrounded con ""
        i++;
      }   
    }    
    else
        printf("we set export\n");
        // hacer el export de la variable (no idea)
    
    return (0);
}

int ft_unset()
{
    return (0);
}

int ft_env(char *env[])
{
    int i;

    if(!env)
        return (-1);

    i = 0;
    while(env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (0);
}

int ft_exit(int status)
{
    exit(status);
    return (0);
}

void ft_init_builtins(t_built_in_type builtins[])
{
    //echo
    builtins[0].built_in_name = "echo";
    builtins[0].foo = ft_echo; 
    //cd
    builtins[1].built_in_name = "cd";
    builtins[1].foo = ft_cd;
    //pwd
    builtins[2].built_in_name = "pwd";
    builtins[2].foo = ft_pwd;
    
    //export
    builtins[3].built_in_name = "export";
    builtins[3].foo = ft_export;
    
    //unset
    builtins[4].built_in_name = "unset";
    builtins[4].foo = ft_unset;

    //env
    builtins[5].built_in_name = "env";
    builtins[5].foo = ft_env;
    
    //exit
    builtins[6].built_in_name = "exit";
    builtins[6].foo = ft_exit; 
    
}