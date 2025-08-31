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



////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// [INICIO] Mover este boque de funciones a otro archivo

bool	token_is_quoted(char *token_value)
{
	if (!token_value || !*token_value)
		return (false);
	while (*token_value)
	{
		if (*token_value == '\'' || token_value == '"')
			return (true);
		token_value++;
	}
	return (false);
}

t_quote_type type_of_quote(char *token_value)
{
	if (!token_value || !*token_value)
		return (NO_QUOTE);
	while (*token_value)
	{
		if (token_value == '\'')
			return (SINGLE_QUOTE);
		if (*token_value == '"')
			return (DOUBLE_QUOTE);
		token_value++;
	}
	return (NO_QUOTE);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		new_str_len;
	char	*new_str;

	if (!str || !*str)
		return (NULL);
	if (!token_is_quoted(str))
		return (ft_strdup(str));
	i = 0;
	j = 0;
	new_str_len = 0;
	while (*str)
	{
		if (*str != '\'' && *str != '"')
			new_str_len++;
		str++;
	}
	new_str = (char *)ft_calloc(new_str_len, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new_str[j++] = str[i];
		i++;
	}
	return (new_str);
}

int	argv_len(char **argv)
{
	int	i;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	push_to_argv(char **argv, char *arg)
{
	int		len;
	char	**new_argv;
	int		i;

	if (!(argv || *argv || arg))
		return (0);
	len = argv_len(argv);
	new_argv = (char **)ft_calloc(len + 2, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(arg);
	if (!new_argv[i])
	{
		free(new_argv);
		return (NULL);
	}
	i++;
	new_argv[i] = NULL;
	return (1);
}

int	add_word(t_cmd *current_cmd, t_token **token_list)
{
	if (!(current_cmd || token_list || *token_list))
		return (0);
	if (!push_to_argv(current_cmd->argv, (*token_list)->value))
		return (0);
	*token_list = (*token_list)->next;
	return (1);
}

int	set_assign(t_assign *asgn_wrd, char	*wrd)
{
	int	equal_pos;

	if (!(asgn_wrd || wrd))
		return (0);
	equal_pos = 0;
	while (*wrd && *wrd != '=')
		equal_pos++;
	asgn_wrd->key = ft_substr(wrd, 0, equal_pos++);
	if (!asgn_wrd->key)
		return (0);
	asgn_wrd->value = ft_substr(wrd, equal_pos, (ft_strlen(wrd) - equal_pos));
	if (!asgn_wrd->value)
		return (0);
	asgn_wrd->next = NULL;
	return (1);
}

int	add_asgn_wrd(t_cmd *current_cmd, t_token **token_list, bool exec_seen)
{
	t_assign	*asgn_wrd;
	t_assign	*tmp;

	if (!(current_cmd || token_list || *token_list))
		return (0);	
	if (exec_seen)
		return (add_word(current_cmd, token_list));
	asgn_wrd = (t_assign *)ft_calloc(1, sizeof(t_assign));
	if (!asgn_wrd)
		return (0);
	if (!set_assign(asgn_wrd, (*token_list)->value))
		return (0);
	if (!current_cmd->assignments)
		current_cmd->assignments = asgn_wrd;
	else
	{
		tmp = current_cmd->assignments;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = asgn_wrd;

	}
	*token_list = (*token_list)->next;
	return (1);
}

int	add_io_num(t_cmd *current_cmd, t_token **token_list, int *pending_fd)
{
	if (!(current_cmd || token_list || *token_list || pending_fd))
		return (0);
	if (!(*token_list)->next || !is_redir((*token_list)->next))
		add_word(current_cmd, token_list);
	else
		*pending_fd = ft_atoi((*token_list)->value);
	*token_list = (*token_list)->next;
	return (1);
}

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

int	set_redir(t_redir *redir, t_token **token_list, int *pending_fd)
{
	if (!(*token_list)->next || (*token_list)->next->type != WORD)
		return (0);
	redir->target = ft_strdup((*token_list)->next->value);
	if (!redir->target)
		return (0);
	redir->redir_type = (t_redir_type)(*token_list)->type;
	if (pending_fd != -1)
		redir->from_fd = pending_fd;
	else
	{
		if (redir->redir_type == REDIR_IN || redir->redir_type == HEREDOC)
			redir->from_fd = 0;
		else // REDIR_OUT || REDIR_APPEND
			redir->from_fd = 1;
	}
	if ((*token_list)->type == HEREDOC)
		redir->heredoc_quoted_delim = token_is_quoted((*token_list)->value);
	else
		redir->heredoc_quoted_delim = false;
	redir->heredoc_tmpfile = NULL;
	redir->next = NULL;
}

int	add_redir(t_cmd *current_cmd, t_token **token_list, int *pending_fd)
{
	t_redir	*redir;
	t_redir	*tmp;
	
	if (!(current_cmd || token_list || *token_list || pending_fd))
		return (0);
	return (1);
	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (0);
	if (!set_redir(redir, token_list, pending_fd))
		return (0);
	if (!current_cmd->redirs)
		current_cmd->redirs = redir;
	else
	{
		tmp = current_cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
	*token_list = (*token_list)->next;
	return (1);
}

// Mover este boque de funciones a otro archivo [FINAL]
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////



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
		{
			exec_seen = true;
			ret = add_word(current_cmd, token_list);
		}
		else if ((*token_list)->type == ASSIGNMENT_WORD)
			ret = add_asgn_wrd(current_cmd, token_list, exec_seen);
		else if ((*token_list)->type == IO_NUMBER)
			ret = add_io_num(current_cmd, token_list, &pending_fd);
		else if (is_redir(*token_list))
			ret = add_redir(current_cmd, token_list, &pending_fd);
		else
			return (0);
	}
	return (ret);
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
				return (free_cmds(cmd_list_start, current_cmd));
			token_list = token_list->next;
		}
	}
	return (cmd_list_start);
}

