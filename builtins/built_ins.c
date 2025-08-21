/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:09:08 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/19 18:24:54 by aumoreno         ###   ########.fr       */
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

int ft_check_built_in(char *cmd, char built_ins[])
{
    int i = 0;
    while(i < 7) 
    {
        if(!ft_strcmp(cmd, built_ins[i]))
            return(1);
        i++;
    }
    return (0);
}


// TO-DO: refact funciones built ins
void ft_built_ins(t_cmd *cmd, t_env *env)
{
	if(!ft_strcmp("echo", cmd->cmd_name))
		ft_echo(cmd->args, NULL);
	else if(!ft_strcmp("cd", cmd->cmd_name))
		ft_cd(NULL, env);
	else if(!ft_strcmp("pwd", cmd->cmd_name))
		ft_pwd();
	else if(!ft_strcmp("export", cmd->cmd_name))
	{
		char *args[] = {"A=\"Valor1\"","B=\"Valor2\"", NULL};
		ft_export(args, g_data);
	}
	else if(!ft_strcmp("unset", cmd->cmd_name))
	{
		char *args[] = {"A","B", NULL};
		ft_unset(args, g_data);
	}
	else if(!ft_strcmp("env", cmd->cmd_name))
	   ft_env(g_data);
	else if(!ft_strcmp("exit", cmd->cmd_name))
		ft_exit(1);
}

