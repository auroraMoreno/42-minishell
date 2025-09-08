/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:01:23 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 11:14:22 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_in(t_redir *redir, t_cmd *cmd)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd < 0 || (redir->redir_type == R_IN
			&& access(redir->target, R_OK) != 0))
		ft_putendl_fd("FD error", STDOUT_FILENO);
	cmd->fd_in = fd;
}

void	ft_redir_out(t_redir *redir, t_cmd *cmd)
{
	int	fd;

	fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_putendl_fd("FD error", STDOUT_FILENO);
	cmd->fd_out = fd;
}

void	ft_redir_append(t_redir *redir, t_cmd *cmd)
{
	int	fd;

	fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		ft_putendl_fd("FD error", STDOUT_FILENO);
	cmd->fd_out = fd;
}

void	ft_handle_redirections(t_redir *redir, t_cmd *cmd)
{
	char	*tmp_file;
	int		fd;

	if (redir->redir_type == R_IN)
		ft_redir_in(redir, cmd);
	else if (redir->redir_type == R_OUT)
		ft_redir_out(redir, cmd);
	else if (redir->redir_type == R_APPEND)
		ft_redir_append(redir, cmd);
	else if (redir->redir_type == R_HEREDOC)
	{
		tmp_file = ft_heredoc(redir->target);
		redir->heredoc_tmpfile = tmp_file;
		fd = open(redir->heredoc_tmpfile, O_RDONLY);
		if (fd == -1)
		{
			ft_putendl_fd("Error opening heredoc file", STDOUT_FILENO);
			exit(EXIT_FAILURE);
		}
		cmd->fd_in = fd;
	}
}

void	ft_close_unused_fds(t_cmd *cmd_list, t_cmd *current)
{
	t_cmd	*cmd;

	cmd = cmd_list;
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
