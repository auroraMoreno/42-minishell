/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:02:06 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/04 13:42:07 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd_errors(int err_number, t_data *data)
{
    if (err_number == EACCES)
        return ft_formatted_error("Permission denied", "-bash: cd", data);
    else if (err_number == ENOENT)
        return ft_formatted_error("No such file or directory", "-bash: cd", data);
    else if (err_number == ENOTDIR)
        return ft_formatted_error("Not a directory", "-bash: cd", data);
    //else 
    return (ft_formatted_error(strerror(err_number), "-bash: cd", data)); //mejorar esto
}

char *ft_cd_go_home(char **env_cpy, char *path)
{
    int i;
    path = NULL;

    i = 0;
    while(env_cpy[i])
    {
        if (!ft_strncmp(env_cpy[i], "HOME", 5))
        {
            path = env_cpy[i] + 5;
            return (path);
        }
        i++;
    }
    return (NULL);
}

/* Buscar el índice de una variable en env_cpy */
int ft_find_env_index(char **env_cpy, const char *key)
{
    int i = 0;
    size_t key_len = ft_strlen(key);
    while (env_cpy[i])
    {
        if (!ft_strncmp(env_cpy[i], key, key_len) && env_cpy[i][key_len] == '=')
            return i;
        i++;
    }
    return -1;
}

/* Cambiar PWD o OLDPWD en env_cpy */
void ft_update_env(char **env_cpy, char *key, char *value)
{
    int idx = ft_find_env_index(env_cpy, key);
    char *new_entry = ft_strjoin(key, "=");
    char *tmp = ft_strjoin(new_entry, value);
    free(new_entry);

    if (idx >= 0)
    {
        free(env_cpy[idx]);
        env_cpy[idx] = tmp;
    }
    else
    {
        // Si no existe, agregarla
        env_cpy = ft_add_env_cpy(env_cpy, key, value); // tu función para añadir
    }
}

int ft_cd(t_cmd *cmd, t_data *data)
{
    char *path = NULL;
    char *old_path;
    char *new_path;

    //guardamos pwd para OLD_PWD
    old_path = getcwd(NULL,0); //FREE THIS
    if(!old_path)
       return(ft_formatted_error("path not found", "pwd", data));
    
    //si no tiene argumentos rollo no tiene cd /home
    //cd sin argumentos => home
    /*
        0 es el exe
        1 argumentos
        2 debe dar error 
    */
    if(!cmd->argv[1]) //ponerse de acuerdo
    {
        path = ft_cd_go_home(data->env_cpy, path);
        if(!path)
        {
            free(old_path);
            return (ft_formatted_error("HOME not set", "-bash: cd",data));
        }
    }
    else if(cmd->argv[2]) //too many arguments
    {
        free(old_path);
        return (ft_formatted_error("too many arguments", "-bash: cd", data));
    }
    else 
        path = cmd->argv[1];
        
    if(chdir(path) == -1)
    {
        free(old_path);
        return(ft_cd_errors(errno, data));
    }
        
    //cambiar el oldpwd y pwd de env    
    new_path = getcwd(NULL,0);
    if(!new_path)
    {
        free(old_path);
        return(ft_formatted_error("path not found", "pwd", data));
    }
                 
    ft_update_env(data->env_cpy, "OLDPWD", old_path);
    ft_update_env(data->env_cpy, "PWD", new_path);
    
    free(new_path);
    free(old_path);
    return (0);
}
