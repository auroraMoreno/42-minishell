/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:44:45 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/06 20:32:37 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_get_key(char *str)
{
    int i = 0;

    while(str[i] && str[i] != '=')
        i++;
      
    return(ft_substr(str, 0, i));
}

char **ft_add_env_cpy(char **env_cpy, char *key, char *value)
{
	int env_len;
	char *new_var;
	char *temp;
	char **new_env;

	if(value == NULL)
		return (env_cpy);
	env_len = ft_get_env_size(env_cpy);
	temp = ft_strjoin(key,"=");
	new_var = ft_strjoin(temp, value);
	new_env = ft_calloc(env_len + 2, sizeof(char *));

	int i = 0;
	while(i < env_len)
	{
		new_env[i] = env_cpy[i];
		// printf("old_env: %s\n", env_cpy[i]);
		// printf("new_env: %s\n", new_env[i]);
		i++;
	}
	
	new_env[env_len] = new_var;
	new_env[env_len + 1] = NULL;
	

	free(temp);
	//free(new_var);
	free(env_cpy);
	return new_env;	
}

int ft_find_in_env_cpy(char **env, char *key)
{
    int i = 0;
    char *curr_key;
    
    while(env[i])
    {
      curr_key = ft_get_key(env[i]);
      
      if(ft_strcmp(curr_key, key) == 0)
      {
        free(curr_key);
        return (i);
      }
      free(curr_key);
      i++;
    }

    return (-1);
}

int ft_check_variables(char *var)
{
    int i;
    if(!var || !var[0] || var[0] == '=')
      return (0);
    //si no empieza con _ o no es letra
    if(!(ft_isalpha(var[0]) || var[0] == '_'))
      return (0);
    
    i = 1;
    while(var[i] && var[i] != '=')
    {
        if(!(ft_isalnum(var[i]) || var[i] == '_'))
          return(0);
        i++;
    }
    
    return (1);
      
}

// Función para ordenar el array env alfabéticamente por la clave
char **ft_sort_alpha(char **env) {
    int i = 0, j;
    int len = ft_get_env_size(env);
    char *aux;
	
    while (i < len - 1) {
        j = 0;
        while (j < len - i - 1) {

            if (strcmp(ft_get_key(env[j]), ft_get_key(env[j + 1])) > 0) {
                aux = env[j];
                env[j] = env[j + 1];
                env[j + 1] = aux;
            }
            j++;
        }
        i++;
    }
    return (env);
}
