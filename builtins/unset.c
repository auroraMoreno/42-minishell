/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:04:00 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/06 18:01:19 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_remove_element(char ***env_cpy, char *var_name)
{
    int i = 0;
    int j = 0;
    char **new_env;
    int size;
    char **old_env = *env_cpy;

    size = ft_get_env_size(old_env);
    new_env = malloc(sizeof(char *) * size); // size-1 + NULL
    if (!new_env)
        return (-1);

    while (old_env[i])
    {
        if (ft_strncmp(old_env[i], var_name, ft_strlen(var_name)) != 0 ||
            old_env[i][ft_strlen(var_name)] != '=') // Para asegurar coincidencia exacta
        {
            new_env[j++] = old_env[i];
        }
        else
            free(old_env[i]);
        i++;
    }
    new_env[j] = NULL;

    free(old_env);
    *env_cpy = new_env;
    return (0);
}

int ft_unset(t_cmd *cmd, t_data *data)
{
    int i; 
    // si var name vacio no pasa nada
    i = 1;
    while(cmd->argv[i]) // aqui me llega nada mas que un string
    {
        if(ft_remove_element(&(data->env_cpy), cmd->argv[i]) == -1)
            return (-1);
        i++;
    }
    return (0);
}
