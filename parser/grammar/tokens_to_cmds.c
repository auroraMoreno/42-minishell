#include "../minishell.h"

int	new_cmd(t_cmd **current_cmd)
{
	*current_cmd = NULL;
	*current_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!*current_cmd)
		return (0);
	(*current_cmd)->argv = NULL;
	(*current_cmd)->assignments = NULL;
	(*current_cmd)->redirs = NULL;
	(*current_cmd)->is_builtin = false;
	(*current_cmd)->next = NULL;
	return (1);
}

int	craft_cmd(t_cmd *current_cmd, t_token **token_list)
{
	bool	exec_seen; // TO DO: ver por qué usarlo
	int		pending_fd; // TO DO: ver por qué usarlo
	int		ret;

	if (!current_cmd || !*token_list || !(*token_list)->value)
		return (0);
	exec_seen = false;
	pending_fd = -1;
	while (*token_list && (*token_list)->type != PIPE)
	{
		if ((*token_list)->type == WORD)
			ret = add_word(current_cmd, token_list, &exec_seen);
		else if ((*token_list)->type == ASSIGNMENT_WORD)
			ret = add_asgn_wrd(current_cmd, token_list, &exec_seen);
		else if ((*token_list)->type == IO_NUMBER)
			ret = add_io_num(current_cmd, token_list, &pending_fd, &exec_seen);
		else if (is_redir(*token_list))
			ret = add_redir(current_cmd, token_list, &pending_fd);
		else
			return (0);
		if (!ret)
			return (0);
	}
	return (1);
}

int	content_in_cmd(t_cmd *current_cmd)
{
	if (!current_cmd)
		return (0);
	if ((current_cmd->argv && current_cmd->argv[0])
		|| current_cmd->assignments
		|| current_cmd->redirs)
		return (1);
	return (0);
}

void	add_cmd(t_cmd **cmd_lst_start, t_cmd **cmd_lst_end, t_cmd *current_cmd)
{
	if (!*cmd_lst_start)
	{
		*cmd_lst_start = current_cmd;
		*cmd_lst_end = *cmd_lst_start;
	}
	else
	{
		(*cmd_lst_end)->next = current_cmd;
		*cmd_lst_end = current_cmd;
	}
	return ;
}

t_cmd	*tokens_to_cmds(t_token *token_list)
{
	t_cmd	*cmd_list_start;
	t_cmd	*cmd_list_end;
	t_cmd	*current_cmd;

	if (!token_list || token_list->type == PIPE)
		return (NULL);
	cmd_list_start = NULL;
	cmd_list_end = NULL;
	while (token_list)
	{
		if (!new_cmd(&current_cmd))
			return (free_cmds(cmd_list_start, NULL));
		if (!craft_cmd(current_cmd, &token_list))
			return (free_cmds(cmd_list_start, current_cmd));
		if (!content_in_cmd(current_cmd))
			return (free_cmds(cmd_list_start, current_cmd));
		add_cmd(&cmd_list_start, &cmd_list_end, current_cmd);
		if (token_list && token_list->type == PIPE)
		{
			if (!token_list->next || token_list->next->type == PIPE)
				return (free_cmds(cmd_list_start, NULL));
			token_list = token_list->next;
		}
	}
	return (cmd_list_start);
}
