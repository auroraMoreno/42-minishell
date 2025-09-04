/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:04:00 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/04 12:34:18 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_remove_element(char **env_cpy, char *var_name)
{
    int i = 0;
    int j = 0;
    char **new_env;
    int size;

    size = ft_get_env_size(env_cpy);
    new_env = malloc(sizeof(char *) * size); // size-1 + NULL
    if (!new_env)
        return (-1);
        
    while (env_cpy[i])
    {
        if (ft_strncmp(env_cpy[i], var_name, ft_strlen(var_name)) != 0)
        {
            new_env[j++] = env_cpy[i];
        }
        else
            free(env_cpy[i]); // liberar el que vamos a borrar
        i++;
    }
    new_env[j] = NULL;

    free_matrix(env_cpy);
    env_cpy = new_env;
    return (0);
}


int ft_unset(t_cmd *cmd, t_data *data)
{
    int i; 
    // si var name vacio no pasa nada
    i = 1;
    while(cmd->argv[i]) // aqui me llega nada mas que un string
    {
        if(ft_remove_element(data->env_cpy, cmd->argv[i]) == -1)
            return (-1);
        i++;
    }
    return (0);
}
