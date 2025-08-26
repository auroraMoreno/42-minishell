/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/26 20:08:07 by aumoreno         ###   ########.fr       */
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

void ft_process_values(char *key_val, char **key,  char **val) // tengo que hacer un dup 
{   
    //voy hasta el igual 
    key = ft_find_equal_sign(key_val);
    // voy hasta despues del igual:
    val = ft_substr(key_val, ft_strlen(key) + 1 ,ft_strlen(key_val) - ft_strlen(key) + 1);
}

void ft_add_env_cpy(char **env_cpy, char *key, char *value)
{
    if(!value)
      return (0);
    
}

int ft_export(t_cmd *cmd, t_data *data)
{
  char *key;
  char *value;
  int i;
  
  if(!cmd->flags)
  {
    ft_print_export(data->env_cpy, cmd); //en orden alfabetico con declare -x ....
    return (0);
  }

  while(cmd->args) // char **args 
  {
      //validar que sea una variable válida
      ft_check_var();
      //buscarla en la env variable 
      ft_process_values(cmd->args[i], &key, &value);
      //si existe => actualizar su valor
      if(getenv(key))
      {
          
      }
      else
      {
        //si no está crearla y add to env: cuando add to env check val, si !val return 0 no hacemos nada 
        ft_add_to_env_cpy(data->env_cpy, key, value);
      }

      i++;
  }
}



int ft_export_old(t_cmd *cmd , t_data *data)
{

    t_list *curr;
    t_env *env; 
    t_list *new;
    int i;
    
    // export no args
    if(!var_name) 
    {
        
      curr = data->env;
      while(curr)
      { 
        env = curr->content; 
        printf("declare -x %s=\"%s\" \n",env->key, env->value);
        curr = curr->next;
      }  
    }    
    else
    {
        //si export + var_name="value"
        i = 0;
        while(var_name[i])
        {
            new = ft_process_env_values(var_name[i]); // TO-DO: quitarles las comillas del final 
            if(!new)
                ft_error("error en set var");
            ft_lstadd_back(&data.env, new);
            i++;
        }        
        // si export + var_name
        //si export + $var_name DUDA
    }
    return (0);
}
