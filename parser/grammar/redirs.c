#include "../minishell.h"

int	is_redir(t_token *token_list)
{
	if (!token_list)
		return (0);
	if (token_list->type == REDIR_IN
		|| token_list->type == REDIR_OUT
		|| token_list->type == REDIR_APPEND
		|| token_list->type == HEREDOC)
		return (1);
	return (0);
}

int	add_io_num(t_cmd *current_cmd, t_token **token_list, int *pending_fd, bool *exec_seen)
{
	long long	val;
	
	if (!current_cmd || !token_list || !*token_list || !pending_fd)
		return (0);
	if (!(*token_list)->next || !is_redir((*token_list)->next))
		return (add_word(current_cmd, token_list, exec_seen));
	else
		val = ft_atoi((*token_list)->value);
	if (val < 0 || val > INT_MAX)
		return (add_word(current_cmd, token_list, exec_seen));
	*pending_fd = (int)val;
	*token_list = (*token_list)->next;
	return (1);
}

int catalogue_redir(t_redir_type *redir_type, t_token_type token_type)
{
	if (token_type == REDIR_IN)
		*redir_type = R_IN;
	else if (token_type == REDIR_OUT)
		*redir_type = R_OUT;
	else if (token_type == REDIR_APPEND)
		*redir_type = R_APPEND;
	else if (token_type == HEREDOC)
		*redir_type = R_HEREDOC;
	else
		return (0);
	return (1);
}

int	set_redir(t_redir *redir, t_token **token_list, int *pending_fd)
{
	t_token	*next;

	next = (*token_list)->next;
	if (!next || next->type == PIPE || is_redir(next))
		return (0);
	redir->target = copy_str(next->value);
	if (!redir->target)
		return (0);
	if (!catalogue_redir(&(redir)->redir_type, (*token_list)->type))
	{
		free (redir->target);
		return (0);
	}
	if (*pending_fd != -1)
		redir->from_fd = *pending_fd;
	else if (redir->redir_type == R_IN || redir->redir_type == R_HEREDOC)
		redir->from_fd = 0;
	else // REDIR_OUT || REDIR_APPEND
		redir->from_fd = 1;
	if ((*token_list)->type == HEREDOC)
		redir->heredoc_quoted_delim = token_is_quoted(next->value);
	else
		redir->heredoc_quoted_delim = false;
	redir->heredoc_tmpfile = NULL;
	redir->next = NULL;
	return (1);
}

int	add_redir(t_cmd *current_cmd, t_token **token_list, int *pending_fd)
{
	t_redir	*redir;
	t_redir	*tmp;

	if (!current_cmd || !token_list || !*token_list || !pending_fd)
		return (0);
	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (0);
	if (!set_redir(redir, token_list, pending_fd))
	{
		free (redir);
		return (0);
	}
	if (!current_cmd->redirs)
		current_cmd->redirs = redir;
	else
	{
		tmp = current_cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
	*token_list = (*token_list)->next->next; // Avanzo 2 (redir + target)
	*pending_fd = -1;
	return (1);
}
