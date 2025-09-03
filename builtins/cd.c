/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:02:06 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/03 21:02:48 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd_errors(int err_number, char *path, t_data *data)
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

char *ft_cd_go_home(t_list *curr, t_env *env, char *path)
{
    t_env *env_node;
    curr = env; 
    path = NULL;
    while(curr)
    {
        env_node = (t_env *) curr->content;
        if (!ft_strncmp(env_node->key, "HOME", 5))
        {
            path = env_node->value;
            break;
        }
        curr = curr->next;
    }
    return (path);
}

int ft_cd(t_cmd *cmd, t_data *data)
{
    char *path;
    char *old_path;
    char *new_path;
    t_list *curr;
    t_env *env_node;
    
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
        path = ft_cd_go_home(curr, data->env, path);
        if(!path)
            return (ft_formatted_error("HOME not set", "-bash: cd",data));
    }
    else if(cmd->argv[2]) //too many arguments
        return (ft_formatted_error("too many arguments", "-bash: cd", data));
    else 
        path = cmd->argv[1];
        
    if(chdir(path) == -1)
        return(ft_cd_errors(errno, path, data));
        
    //cambiar el oldpwd y pwd de env    
    new_path = getcwd(NULL,0);
    if(!new_path)
        return(ft_formatted_error("path not found", "pwd", data));
                 
    curr = data->env;
    while(curr)
    {
        env_node = curr->content;
        if (!ft_strncmp(env_node->key, "OLDPWD", ft_strlen("OLDPWD"))) //TO-DO review this
        {
            free(env_node->value);
            env_node->value = ft_strdup(old_path);
        }
        if(!ft_strncmp(env_node->key, "PWD", ft_strlen("PWD"))) 
        {
            free(env_node->value);
            env_node->value = ft_strdup(new_path);
        }
        curr = curr->next;
    }
    free(new_path);
    free(old_path);
    return (0);
}
