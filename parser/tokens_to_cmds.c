#include "../minishell.h"

int	*new_cmd(void)
{
	t_cmd	*current_cmd;

	current_cmd = NULL;
	current_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!current_cmd)
		return (0);
	current_cmd->argv = NULL;
	current_cmd->assignments = NULL;
	current_cmd->redirs = NULL;
	current_cmd->is_builtin = false;
	current_cmd->next = NULL;
	return (1);
}

int	craft_cmd(t_cmd *current_cmd, t_token **token_list)
{
	int	ret;

	ret = 0;
	if (!current_cmd || !*token_list)
		return (ret);
	while (*token_list && (*token_list)->type != PIPE)
	{
		if ((*token_list)->type == WORD)
			ret = add_word(current_cmd, *token_list);
		else if ((*token_list)->type == IO_NUMBER)
			ret = add_ionum(current_cmd, *token_list);
		else if ((*token_list)->type == ASSIGNMENT_WORD)
			ret = add_assign(current_cmd, *token_list);
		else if ((*token_list)->type == REDIR_IN
			|| (*token_list)->type == REDIR_OUT
			|| (*token_list)->type == REDIR_APPEND
			|| (*token_list)->type == HEREDOC)
			ret = add_redir(current_cmd, *token_list);
		*token_list = (*token_list)->next;
		if (ret == 0)
			return (ret);
	}
	return (ret);
}

int	content_in_cmd(t_cmd *current_cmd)
{
	if (!(current_cmd->argv || current_cmd->assignments || current_cmd->redirs))
		return (0);
	return (1);
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
		if (!new_cmd())
			return (free_cmds(cmd_list_start, NULL));
		if (!craft_cmd(current_cmd, &token_list))
			return (free_cmds(cmd_list_start, current_cmd));
		if (!content_in_cmd(current_cmd))
			return (free_cmds(cmd_list_start, current_cmd));
		add_cmd(&cmd_list_start, &cmd_list_end, current_cmd);
		if (token_list && token_list->type == PIPE)
		{
			if (!token_list->next || token_list->next->type == PIPE)
				return (free_cmds(cmd_list_start, current_cmd));
			token_list = token_list->next;
		}
	}
	return (cmd_list_start);
}

