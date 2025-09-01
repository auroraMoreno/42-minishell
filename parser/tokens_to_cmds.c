#include "../minishell.h"

void	free_assignments(t_assign *assignments)
{
	t_assign *tmp;

	while (assignments)
	{
		tmp	= assignments;
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
		if (*token_value == '\'' || *token_value == '"')
			return (true);
		token_value++;
	}
	return (false);
}

static t_quote_type type_of_quote(char *token_value)
{
	if (!token_value || !*token_value)
		return (NO_QUOTE);
	while (*token_value)
	{
		if (*token_value == '\'')
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

	if (!str)
		return (NULL);
	if (!*str)
		return (ft_strdup(""));
	new_str_len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new_str_len++;
	}
	new_str = (char *)ft_calloc(new_str_len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new_str[++j] = str[i];
	}
	new_str[new_str_len] = '\0';
	return (new_str);
}

char	*copy_str(char *str)
{
	if (!str)
		return (NULL);
	if (!*str)
		return (ft_strdup(""));
	if (!token_is_quoted(str))
		return (ft_strdup(str));
	else
		return (remove_quotes(str));
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

char	**push_to_argv(char **argv, char *arg)
{
	int		len;
	char	**new_argv;
	int		i;

	if (!arg)
		return (NULL);
	len = argv_len(argv);
	new_argv = (char **)ft_calloc(len + 2, sizeof(char *));
	if (!new_argv)
		return (NULL);
	i = -1;
	while (++i < len)
		new_argv[i] = argv[i];
	new_argv[i] = copy_str(arg);
	if (!new_argv[i])
	{
		free(new_argv);
		return (NULL);
	}
	i++;
	new_argv[i] = NULL;
	free (argv);
	return (new_argv);
}

int	add_word(t_cmd *current_cmd, t_token **token_list, bool *exec_seen)
{
	char **tmp;
	
	if (!current_cmd || !token_list || !*token_list || !exec_seen)
		return (0);
	tmp = push_to_argv(current_cmd->argv, (*token_list)->value);
	if (!tmp)
		return (0);
	current_cmd->argv = tmp;
	if (!*exec_seen)
		*exec_seen = true;
	*token_list = (*token_list)->next;
	return (1);
}

int	set_assign(t_assign *asgn_wrd, char	*wrd)
{
	int		i;
	int		equal_pos;
	char	*unquoted_wrd;
	int		pos_to_end;

	if (!asgn_wrd || !wrd)
		return (0);
	unquoted_wrd = copy_str(wrd);
	if (!unquoted_wrd)
		return (0);
	i = 0;
	equal_pos = 0;
	while (unquoted_wrd[i] && unquoted_wrd[i] != '=')
	{
		equal_pos++;
		i++;
	}
	if (equal_pos == ft_strlen(unquoted_wrd))
	{
		free (unquoted_wrd);
		return (0);
	}
	asgn_wrd->key = ft_substr(unquoted_wrd, 0, equal_pos++);
	if (!asgn_wrd->key)
	{
		free (unquoted_wrd);
		return (0);
	}
	pos_to_end = ft_strlen(unquoted_wrd) - equal_pos;
	asgn_wrd->value = ft_substr(unquoted_wrd, equal_pos, pos_to_end);
	if (!asgn_wrd->value)
	{
		free (unquoted_wrd);
		free (asgn_wrd->key);
		return (0);
	}
	asgn_wrd->next = NULL;
	free (unquoted_wrd);
	return (1);
}

int	add_asgn_wrd(t_cmd *current_cmd, t_token **token_list, bool *exec_seen)
{
	t_assign	*asgn_wrd;
	t_assign	*tmp;

	if (!current_cmd || !token_list || !*token_list)
		return (0);	
	if (*exec_seen)
		return (add_word(current_cmd, token_list, exec_seen));
	asgn_wrd = (t_assign *)ft_calloc(1, sizeof(t_assign));
	if (!asgn_wrd)
		return (0);
	if (!set_assign(asgn_wrd, (*token_list)->value))
	{
		free (asgn_wrd);
		return (0);
	}
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
		*redir_type = REDIR_IN;
	else if (token_type == REDIR_OUT)
		*redir_type = REDIR_OUT;
	else if (token_type == REDIR_APPEND)
		*redir_type = REDIR_APPEND;
	else if (token_type == HEREDOC)
		*redir_type = HEREDOC;
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
		return (0);
	if (*pending_fd != -1)
		redir->from_fd = *pending_fd;
	else if (redir->redir_type == REDIR_IN || redir->redir_type == HEREDOC)
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

void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (i)
			printf(" ");
		printf ("%s", argv[i]);
		i++;
	}
	return ;
}

void	print_assgn(t_assign *assign)
{
	t_assign	*tmp;
	int			i;

	tmp = assign;
	i = 0;
	while (tmp)
	{
		if (i)
			printf("\n");
		printf("	assignment %d\n", i);
		printf("		key		= %s\n", tmp->key);
		printf("		value	= %s\n", tmp->value);
		i++;
	}
	return ;
}

void	print_redir_type(t_redir_type redir_type)
{
	char	type_redir;

	if (redir_type == REDIR_IN)
		type_redir = "REDIR_IN";
	else if (redir_type == REDIR_OUT)
		type_redir = "REDIR_OUT";
	else if (redir_type == REDIR_APPEND)
		type_redir = "REDIR_APPEND";
	else if (redir_type == HEREDOC)
		type_redir = "HEREDOC";
	else
		type_redir = "UNKNOWN";
	printf("		redir type = %s\n", type_redir);
	return ;
}


void	print_redir(t_redir *redirs)
{
	t_redir	*tmp;
	int		i;
	char	*redir_type;
	char	*bool_hd_quotes;

	tmp = redirs;
	i = 0;
	while (tmp)
	{
		if (i)
			printf("\n");
		printf("	redir %d\n", i);
		printf("		from_fd		= %d\n", tmp->from_fd);
		print_redir_type(redir_type);
		printf("		target		= %s\n", tmp->target);
		if (tmp->heredoc_quoted_delim)
			bool_hd_quotes = "true";
		else
			bool_hd_quotes = "false";
		printf("		hd_quoted	= %s\n", bool_hd_quotes);
		printf("		hd_tmpfile	= %s\n", tmp->heredoc_tmpfile);
		i++;
	}
	return ;
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;
	char	*is_builtin;

	tmp = cmds;
	i = 0;
	while (tmp)
	{
		printf("CMD %d = \n", i);
		print_argv(tmp->argv);
		print_assgn(tmp->assignments);
		print_redir(tmp->redirs);
		if (tmp->is_builtin)
			is_builtin = "true";
		else
			is_builtin = "false";
		printf("	is builtin = %s\n", is_builtin);
		tmp = tmp->next;
	}
	return ;
}

// TODO
	// synatx error
	// heredoc tmpfile
	// expansions