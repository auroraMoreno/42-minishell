/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:09:08 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/03 16:44:02 by aumoreno         ###   ########.fr       */
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

int ft_export(char *var_name[], t_data data)
{
    //solo el name porq el value se supone que ya está 
    // segun el comportamiento de export si la var a exportar no existe, lista las variables exportadass
    //int i;
    // char *key;
    // char *value;
    t_list *curr;
    t_env *env; 
    int i;
    
    if(!var_name)//list 
    {
        
      curr = data.env;
      while(curr)
      { 
        // t data => t_list env => ese recorro 
        // tengo un metodo init env que le llega un t_list env y envp y devuelve t_list env 
        // cada nodo de t_list env es un tipo t_env  (el content es t_list es tipo void asi que puedo meter lo que yo quiera)
        //
       // key = ft_find_equal_sign(env[i]); // esto me puede servir para el metodo init_env
       // value = ft_substr(env[i], ft_strlen(key) + 2 ,ft_strlen(env[i]) - ft_strlen(key) + 1); // + 1 porq key no tiene el igua, aunq a lo mejor cuenta el null
        env = curr->content; 
        printf("declare -x %s=\"%s\" \n",env->key, env->value); // TO-DO: arregalar que el valor esté surrounded con ""
        curr = curr->next;
      }  
    }    
    else
    {
        // hacer el export de la variable (no idea)
        // pueden venir varias variables asi que deberia de ser un bucle ? 
        //podría usar el método process env 
        i = 0;
        t_list *new;
        while(var_name[i])
        {
            //printf("%s\n", var_name[i]);
            //get hasta el equal para el key
            //guargar en un 
            //get despues del equal para el value
            new = ft_process_env_values(var_name[i]); // TO-DO: quitarles las comillas del final 
            if(!new)
                ft_error("error en set var");
            ft_lstadd_back(&data.env, new);
            i++;
        }        
        printf("exported\n");
        // por cada var name: 
            // si export + var_name
            //si export + var_name="value"
        // uso el método lst_add_back 
            // tengo que meter en un t_env los valores que me vengan y luego pasarselo a lst_add_back
        //si export + $var_name DUDA
    }
    return (0);
}

t_list *ft_find_element(t_list *env_list, char *var_name)
{
    t_list *curr;
    t_list *prev;
    //t_list *to_del;
    t_env *env;
    
    curr = env_list;
    prev = NULL;
    while(curr)
    {
        env = curr->content;
        if(!ft_strncmp(env->key, var_name, ft_strlen(var_name) + 1))
        {
             //todo esto es para unlink el estupido nodo 
            if(prev)
                prev->next = curr->next;
            else 
                env_list = curr->next;
        }
        prev = curr;
        curr = curr->next;
    }
    return (curr);
}


int ft_unset(char *var_names[], t_data data)
{
    t_list *to_del;

    int i;
    // si var name vacio no pasa nada
    if(var_names)
    {
        i = 0;
        while(var_names[i]) // aqui me llega nada mas que un string
        {
            //encontrar en la lista data.env el var_name[i]
            // apartir de aqui todo va a ir dentro de una funcion a parte: 
            
            to_del = ft_find_element(data.env, var_names[i]); //TO_DO: gestion errores si no existe bla bla, hacer same en export
            //t_env *test = to_del->content;
            //pasarselo a delone
            //ft_free_env_node(to_del->content);
            ft_lstdelone(to_del, ft_free_env_node); //pues no va
            //printf("found %s\n", test->key);
            printf("var unset\n");
            i++;
        }
    }
    
    
    return (0);
}

int ft_env(t_data data) //TO-DO: cambiar esto a t_data
{
    t_list *curr;
    t_env *env; 
      
    curr = data.env;
    while(curr)
    { 
    // t data => t_list env => ese recorro 
    // tengo un metodo init env que le llega un t_list env y envp y devuelve t_list env 
    // cada nodo de t_list env es un tipo t_env  (el content es t_list es tipo void asi que puedo meter lo que yo quiera)
    //
    // key = ft_find_equal_sign(env[i]); // esto me puede servir para el metodo init_env
    // value = ft_substr(env[i], ft_strlen(key) + 2 ,ft_strlen(env[i]) - ft_strlen(key) + 1); // + 1 porq key no tiene el igua, aunq a lo mejor cuenta el null
    env = curr->content; 
    printf("%s=%s\n",env->key, env->value); // TO-DO: arregalar que el valor esté surrounded con ""
    curr = curr->next;
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