/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/26 12:50:57 by aumoreno         ###   ########.fr       */
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


int ft_export(t_cmd *cmd, t_data *data)
{
  char **cpy_env;
  if(!cmd->flags)
  {
    ft_print_export(data->env_cpy, cmd); //en orden alfabetico con declare -x ....
    return (0);
  }

  while(cmd->args)
  {
    
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
