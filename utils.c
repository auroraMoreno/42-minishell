/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:08:59 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/06 20:55:29 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_route(char *instruction, char *path)
{
	char	**routes;
	char	*route;
	char	*cmd_route;
	int		i;

	routes = ft_split(path, ':');
	if (!routes)
		return (0);
	i = 0;
	while (routes[i])
	{
		route = ft_strjoin(routes[i], "/");
		cmd_route = ft_strjoin(route, instruction);
		free(route);
		if (access(cmd_route, F_OK) == 0)
		{
			free_matrix(routes);
			return (cmd_route);
		}
		free(cmd_route);
		i++;
	}
	free_matrix(routes);
	return (NULL);
}

char	*get_route(char *cmd, char **envp, t_data *data)
{
	int		i;
	int		in_line;
	char	**instructions;
	char	*cmd_route;

	i = 0;
	in_line = -1;
	while (envp[i] && in_line == -1)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			in_line = i;
		i++;
	}
	if (in_line == -1)
		ft_error_and_free("command not found", 127, data);
	instructions = ft_split(cmd, ' ');
	if (!instructions)
		return (NULL);
	cmd_route = find_route(instructions[0], &envp[in_line][5]);
	free_matrix(instructions);
	if (!cmd_route)
		return (NULL);
	return (cmd_route);
}


int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;
        
    while(s1[i] || s2[i])
    {
        if(s1[i] == s2[i])
            i++;
        else if(s1[i] != s2[i])
		    return (1);
    }
    return (0);
}

t_list *ft_process_env_values(char *key_val) // tengo que hacer un dup 
{
    t_env *env;
    t_list *new;

    env = (t_env *)malloc(sizeof(t_env));
    if(!env)
        return (0);
    ft_process_values(key_val, &env->key, &env->value);
    if(!env->key)
    {
        //TO-DO: free memory
        return (0);
    }
    // creo nuevo nodo de la lista
    new = ft_lstnew(env);
    
    if(!new)
    {
        //TO-DO: free

        return (0);
    }
    //devuelvo ese nuevo nodo 
    return (new);
}
