/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:04:52 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/07 23:19:22 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmd(t_cmd *cmd, t_data *data, t_cmd *cmd_list)
{
	int		exit_code;
	char	*path;
	char 	*cwd;
	char	*temp;
	char	*key;
	
	if(cmd->is_builtin)
	{
		exit_code = ft_built_ins(cmd, data);
		if(exit_code != -1)
		{
			//ft_free_all(data, cmd_list);
			exit(exit_code);
		}
	}
	key = ft_get_key("PATH");
	if(!cmd->argv[0])
	{
		free(key);
		ft_error_and_free("command not found", 127, data, cmd_list);
	}
	if(!key)
	{
		free(key);
		ft_formatted_error("command not found", "bash: ", data);
	}
	else
	{
		if (cmd->argv[0][0] == '/')
			path = cmd->argv[0];
		else if (cmd->argv[0][0] == '.')
		{
			cwd = getcwd(NULL, 0);
			if (cwd == NULL)
				ft_error_and_free("getcwd error", 1, data, cmd_list);
			path = ft_strjoin(cwd, "/");
			if (!path)
				ft_error_and_free("malloc error", 1, data, cmd_list);
			temp = ft_strjoin(path, cmd->argv[0]);
			free(path);
			path = temp;
			free(cwd);
		}
		else
			path = get_route(cmd->argv[0], data->env_cpy, data);

		if (!path)
        {
            free(key);  // Liberar key antes de salir
            ft_error_and_free("command not found", 127, data, cmd_list);
        }

		
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
			
		free(key);
		execve(path,cmd->argv, data->env_cpy);
		free(path);
		if(errno == EACCES)
			ft_error_and_free("permission denied", 126, data, cmd_list);  
		else if(errno == ENOENT)
			ft_error_and_free("command not found" ,127, data, cmd_list); 
		else 
			ft_error_and_free("command not found", 1, data, cmd_list);

	}

}

void	ft_close_unused_fds(t_cmd *cmd_list, t_cmd *current)
{
	t_cmd *cmd = cmd_list;

	while (cmd)
	{
		if (cmd != current)
		{
			if (cmd->fd_in != STDIN_FILENO)
				close(cmd->fd_in);
			if (cmd->fd_out != STDOUT_FILENO)
				close(cmd->fd_out);
		}
		cmd = cmd->next;
	}
}

pid_t	ft_create_fork(t_cmd *cmd, t_data *data, t_cmd *cmd_list)
{
	pid_t	process_id;

	if(cmd->fd_in == -1 || cmd->fd_out == -1)
		return (-1);
	process_id = fork();
	if(process_id == -1)
		return (FORK_ERROR);
	else if(process_id == 0)
	{
		if(dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return(FORK_ERROR);
		if(dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return(FORK_ERROR);
		
		ft_close_unused_fds(cmd_list, cmd);
			
		ft_exec_cmd(cmd, data, cmd_list);
	}
	return (process_id);
}

t_cmd	*ft_cmd_last(t_cmd *cmd_list)
{
	if (!cmd_list)
		return (NULL);
	while (cmd_list->next)
		cmd_list = cmd_list->next;
	return (cmd_list);
}

int	ft_wait_children_process(t_cmd *cmd_list)
{
	int		exit_status;
	t_cmd	*cmd = cmd_list;
	t_cmd	*last;

	if (!cmd_list)
		return (1);
	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->id_process != -1)
			waitpid(cmd->id_process, &exit_status, 0);
		cmd = cmd->next;
	}
	last = ft_cmd_last(cmd_list);

	if (!last || last->id_process == -1)
		return (1);

	return (ft_return_status(exit_status));
}

int	ft_return_status(int status)
{
	int	exit_code;
	
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		exit_code = WTERMSIG(status);
		if (exit_code == SIGINT)
			ft_putchar_fd('\n', 1);
		else if (exit_code == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		exit_code = exit_code + 128;
	}
	else  
		exit_code = -1;
	return (exit_code);
}
