#include "../minishell.h"

t_token_type	get_token_type(char	*token)
{
	int	len;

	len = ft_strlen(token);
	if (!ft_strncmp(token, "|", len))
		return (PIPE);
	else if (!ft_strncmp(token, "<", len))
		return (REDIR_IN);
	else if (!ft_strncmp(token, ">", len))
		return (REDIR_OUT);
	else if (!ft_strncmp(token, "<<", len))
		return (HEREDOC);
	else if (!ft_strncmp(token, ">>", len))
		return (REDIR_APPEND);
	else
		return (WORD);
}

t_token	*new_token(char	*token, t_token_type token_type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = token;
	new->type = token_type;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return ;
}

void	print_list(t_token *token_list)
{
	int		i;
	char	*type;

	i = 1;
	while (token_list)
	{
		if (token_list->type == PIPE)
			type = "PIPE";
		else if (token_list->type == REDIR_IN)
			type = "REDIR_IN";
		else if (token_list->type == REDIR_OUT)
			type = "REDIR_OUT";
		else if (token_list->type == HEREDOC)
			type = "HEREDOC";
		else if (token_list->type == REDIR_APPEND)
			type = "REDIR_APPEND";
		else
			type = "WORD";
		printf("token %d in list = %s (type = %s)\n", i, token_list->value, type);
		token_list = token_list->next;
		i++;
	}
	return ;
}

t_token	*insert_tokens_in_list(char	**tokens)
{
	t_token	*token_list;
	t_token	*token_node;
	int		i;

	token_list = NULL;
	i = 0;
	while (tokens[i])
	{
		token_node = new_token(ft_strdup(tokens[i]), get_token_type(tokens[i]));
		add_token(&token_list, token_node);
		i++;
	}
	print_list(token_list);
	return (token_list);
}
