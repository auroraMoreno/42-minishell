/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:02:06 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/06 15:44:09 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd_errors(int err_number, char *path)
{
    char *err;
    char *aux;
    err = ft_strjoin("-bash: cd: ", path);
    if(!err)
        ft_error("Error allocating");
    if(err_number == EACCES)
        aux = ft_strjoin(err, ": Permission denied");
    else if(err_number == ENOENT)
        aux = ft_strjoin(err, ": No such file or directory");
    else if (err_number == ENOTDIR)
        aux = ft_strjoin(err, ": Not a directory");
    else 
        aux = NULL;
    free(err);
    if(aux)
    {
        ft_putendl_fd(aux, 2);
        free(aux);
    }
}

int ft_cd(char *path, t_list *env)
{
    t_list *curr;
    t_env *env_node;
    char new_path[PATH_MAX];
    path = "../only_sudo"; //TO-DO: CAMBIAR
    if(chdir(path) == -1)
    {
        ft_cd_errors(errno, path);
        return (errno);
    }
    //cambiar el oldpwd y pwd de env    
    getcwd(new_path, sizeof(new_path));                 
    curr = env;
    while(curr)
    {
        env_node = curr->content; 
        if(!ft_strncmp(env_node->key, "PWD", ft_strlen("PWD"))) // TO-DO: cambiar el OLD_PWD tmnb? 
        {
            free(env_node->value);
            env_node->value = new_path;
            break;
        }
        curr = curr->next;
    }
    return (0);
}