/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/27 13:07:38 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_env_size(char **env)
{
	int	len;

	len = 0;
	while (*env)
	{
		len++;
		env++;
	}
	return (len);
}

char	**ft_sort_alpha(char **env)
{
	int		i;
	int		j;
	int		len;
	char	*aux;

	i = 0;
	len = ft_get_env_size(env);
	while (i < len)
	{
		j = -1;
		while (++j < (len - i - 1))
		{
			aux = env[j];
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				aux = env[j];
				env[j] = env[j + 1];
				env[j + 1] = aux;
			}
		}
		i++;
	}
	return (env);
}


void ft_print_export(char **env, t_cmd *cmd)
{
    int i;
    char **sorted_env;
    
    i = 0;
    sorted_env = ft_sort_alpha(env);
    while(sorted_env[i])
    {
      ft_putstr_fd("declare -x ", cmd->fd_out);
      ft_putstr_fd(sorted_env[i], cmd->fd_out);
      ft_putstr_fd("\n", cmd->fd_out);
      i++;
    }
}

char *ft_get_key(char *str)
{
    int i = 0;

    while(str[i] && str[i] != '=')
        i++;
      
    return(ft_substr(str, 0, i));
}

void ft_process_values(char *key_val, char **key,  char **val) // tengo que hacer un dup 
{   
  
    char *equal; 
  
    //voy hasta el igual para el key
    *key = ft_get_key(key_val);
    
    //buscar el = 
    equal = ft_strchr(key_val, '=');
    
    if(!equal)
      *val = NULL;
    else if(*(equal + 1) == '\0')
      *val = ft_strdup("");
    else 
      *val = ft_strdup(equal + 1);

}


char **ft_add_env_cpy(char **env_cpy, char *key, char *value)
{
	int env_len;
	char *new_var;
	char *temp;
	char *new_env;

	if(value == NULL)
		return (0);
	env_len = ft_get_env_size(env_cpy);
	temp = ft_strjoin(key,"=");
	new_var = ft_strjoin(temp, value);
	new_env = ft_calloc(env_len + 2, sizeof(char *));

	int i = 0;
	while(i < env_len)
	{
		new_env[i] = env_cpy[i];
		i++;
	}
	
	new_env[i] = new_var;
	new_env[i++] = NULL;
	  

	free(temp);
	free(new_var);
	free_matrix(env_cpy);
	return new_env;	
}

/*
  reglas de bash
  no puede empezar con numeros
    -bash: export: `1try=try': not a valid identifier
  tiene que tener un = (pero si no lo tienen no da error solo no add la variable)
  empezar por una letra o un _ 
  case sensitive
  
*/

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


int ft_find_in_env_cpy(char **env, char *key)
{
    int i = 0;
    char *curr_key;
    
    while(env[i])
    {
      curr_key = ft_get_env_size(env[i]);
      
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

int ft_export(t_cmd *cmd, t_data *data)
{
  char *key;
  char *value;
  int index_key;
  int i;
  
  if(!cmd->args)
  {
    ft_print_export(data->env_cpy, cmd); //en orden alfabetico con declare -x ....
    return (0);
  }

  i = 0;
  while(cmd->args[i]) // char **args 
  {
      //validar que sea un nombre de variable válido
      if(ft_check_variables(cmd->args[i]))
      {
        //get key and value if there is 
        ft_process_values(cmd->args[i], &key, &value);
        //buscarla en la env variable 
        index_key = ft_find_in_env(data->env_cpy, key);
        //si existe => actualizar su valor
        if(index_key >= 0 && value)
        {
            free(data->env_cpy[index_key]);
            char *tmp = ft_strjoin(key, "=");
            char result = ft_strjoin(tmp, value);
            data->env_cpy[index_key] = result;
            free(result);
            free(tmp);
        }
        else if (index_key == -1) //si no existe => la creo 
          data->env_cpy = ft_add_env_cpy(data->env_cpy, key, value);
        
        free(key);
        if(value)
          free(value);
      }
      else
        ft_formatted_error("not a valid identifier", " -bash: export", data);

      i++;
  }

  return (0);
}
