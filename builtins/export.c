/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/04 12:09:59 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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
