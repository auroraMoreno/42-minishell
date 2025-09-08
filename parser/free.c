/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:37:40 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 18:42:55 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**free_tkn_maker(int token_nbr, char *cmd_trimmed, int *delimiters_pos)
{
	char	*err_opn_qt;

	err_opn_qt = "minishell: unexpected EOF while looking for matching quote";
	if (token_nbr == -1)
		ft_putendl_fd(err_opn_qt, 2);
	if (cmd_trimmed)
		free (cmd_trimmed);
	if (delimiters_pos)
		free (delimiters_pos);
	return (NULL);
}

void	free_token_list(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list;
		token_list = token_list->next;
		if (tmp->value)
			free (tmp->value);
		free (tmp);
	}
	return ;
}

void	free_assignments(t_assign *assignments)
{
	t_assign	*tmp;

	while (assignments)
	{
		tmp = assignments;
		assignments = assignments->next;
		if (tmp->key)
			free (tmp->key);
		if (tmp->value)
			free (tmp->value);
		free (tmp);
	}
	return ;
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		if (tmp->target)
			free (tmp->target);
		if (tmp->heredoc_tmpfile)
			free (tmp->heredoc_tmpfile);
		free (tmp);
	}
	return ;
}

t_cmd	*free_cmds(t_cmd *cmd_list_start, t_cmd *current_cmd)
{
	t_cmd	*tmp;

	while (cmd_list_start)
	{
		tmp = cmd_list_start;
		cmd_list_start = cmd_list_start->next;
		if (tmp->argv)
			free_matrix(tmp->argv);
		if (tmp->assignments)
			free_assignments(tmp->assignments);
		if (tmp->redirs)
			free_redirs(tmp->redirs);
		free (tmp);
	}
	if (current_cmd)
	{
		if (current_cmd->argv)
			free_matrix(current_cmd->argv);
		if (current_cmd->assignments)
			free_assignments(current_cmd->assignments);
		if (current_cmd->redirs)
			free_redirs(current_cmd->redirs);
		free (current_cmd);
	}
	return (NULL);
}
