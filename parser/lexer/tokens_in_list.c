/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_in_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:34:41 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 18:44:17 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_assignment(char	*token)
{
	int	i;

	if (!token || !*token)
		return (0);
	if (!(ft_isalpha(token[0]) || token[0] == '_'))
		return (0);
	i = 1;
	while (token[i] && token[i] != '=')
	{
		if (!(ft_isalnum(token[i]) || token[i] == '_'))
			return (0);
		i++;
	}
	return (token[i] == '=');
}

t_token_type	get_token_type(char	*token)
{
	if (!token || !*token)
		return (WORD);
	if (!ft_strncmp(token, "<<", ft_strlen("<<") + 1))
		return (HEREDOC);
	else if (!ft_strncmp(token, ">>", ft_strlen(">>") + 1))
		return (REDIR_APPEND);
	else if (!ft_strncmp(token, "<", ft_strlen("<") + 1))
		return (REDIR_IN);
	else if (!ft_strncmp(token, ">", ft_strlen(">") + 1))
		return (REDIR_OUT);
	else if (ft_is_number(token))
		return (IO_NUMBER);
	else if (ft_is_assignment(token))
		return (ASSIGNMENT_WORD);
	else if (!ft_strncmp(token, "|", ft_strlen("|") + 1))
		return (PIPE);
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

t_token	*tokens_in_list(char	**tokens)
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
	return (token_list);
}
