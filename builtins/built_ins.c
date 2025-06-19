/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:09:08 by aumoreno          #+#    #+#             */
/*   Updated: 2025/06/19 16:57:14 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*file que será init data:*/

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

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

int ft_check_built_in(char *cmd, t_built_in_type built_ins[])
{
    int i = 0;
    while(i < 7)
    {
        if(!ft_strcmp(cmd, built_ins[i].built_in_name))
            return(1);
        i++;
    }
    return (0);
}


t_cmd ft_init_cmd(char *cmd, t_built_in_type built_ins[]) // aqui pueden venir varios 
{
    t_cmd cmd_data; 
    cmd_data.cmd_name = cmd;
    cmd_data.flags = NULL;
    cmd_data.args = NULL;
    cmd_data.cmd_path = find_route(cmd, getenv("PATH"));
    printf("%s", cmd_data.cmd_path);
    //check if built in:
    cmd_data.is_built_in = ft_check_built_in(cmd,built_ins);
    printf("%d", cmd_data.is_built_in);
    return (cmd_data);
}

void ft_init_builtins(t_built_in_type builtins[])
{
    //echo
    builtins[0].built_in_name = "echo";
    builtins[0].foo = ft_echo; 
    
    //cd
    builtins[1].built_in_name = "cd";
    builtins[1].foo = ft_cd;
    
    //pwd
    builtins[2].built_in_name = "pwd";
    builtins[2].foo = ft_pwd;
    
    //export
    builtins[3].built_in_name = "export";
    builtins[3].foo = ft_export;
    
    //unset
    builtins[4].built_in_name = "unset";
    builtins[4].foo = ft_unset;

    //env
    builtins[5].built_in_name = "env";
    builtins[5].foo = ft_env;
    
    //exit
    builtins[6].built_in_name = "exit";
    builtins[6].foo = ft_exit; 
    
}