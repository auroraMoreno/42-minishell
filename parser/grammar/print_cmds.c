#include "../minishell.h"

void	print_argv(char **argv)
{
	int	i;

	if (!argv)
		return;
	i = 0;
	printf("	argv = ");
	while (argv[i])
	{
		if (i)
			printf(" ");
		printf ("%s", argv[i]);
		i++;
	}
	printf("\n");
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
		printf("	assignment %d\n", i++);
		printf("		key	= %s\n", tmp->key);
		printf("		value	= %s\n", tmp->value);
		tmp = tmp->next;
	}
	return ;
}

void	print_redir_type(t_redir_type redir_type)
{
	char	*type_redir;

	if (redir_type == R_IN)
		type_redir = "REDIR_IN";
	else if (redir_type == R_OUT)
		type_redir = "REDIR_OUT";
	else if (redir_type == R_APPEND)
		type_redir = "REDIR_APPEND";
	else if (redir_type == R_HEREDOC)
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
	char	*bool_hd_quotes;

	tmp = redirs;
	i = 0;
	while (tmp)
	{
		if (i)
			printf("\n");
		printf("	redir %d\n", i++);
		printf("		from_fd		= %d\n", tmp->from_fd);
		print_redir_type(tmp->redir_type);
		if (tmp->target)
			printf("		target		= %s\n", tmp->target);
		if (tmp->heredoc_quoted_delim)
			bool_hd_quotes = "true";
		else
			bool_hd_quotes = "false";
		printf("		hd_quoted	= %s\n", bool_hd_quotes);
		if (tmp->heredoc_tmpfile)
			printf("		hd_tmpfile	= %s\n", tmp->heredoc_tmpfile);
		tmp = tmp->next;
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
		printf("CMD %d \n{", i);
		print_argv(tmp->argv);
		print_assgn(tmp->assignments);
		print_redir(tmp->redirs);
		if (tmp->is_builtin)
			is_builtin = "true";
		else
			is_builtin = "false";
		printf("	is builtin = %s\n", is_builtin);
		printf("}\n\n");
		i++;
		tmp = tmp->next;
	}
	return ;
}
