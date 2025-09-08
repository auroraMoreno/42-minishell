/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:31:17 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 18:31:46 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(t_token *token_list, int *last_status)
{
	char	*token_value;

	if (!token_list || !token_list->value || !*token_list->value)
		token_value = "newline";
	else
		token_value = token_list->value;
	if (last_status)
		*last_status = 258;
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(token_value, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

int	check_pipe(t_token *token_list, int count, int *last_status)
{
	if (!token_list)
		return (syntax_error(NULL, last_status));
	if (!count)
		return (syntax_error(token_list, last_status));
	if (!token_list->next)
		return (syntax_error(NULL, last_status));
	if (token_list->next->type == PIPE)
		return (syntax_error(token_list->next, last_status));
	return (1);
}

int	check_redir(t_token *token_list, int *last_status)
{
	if (!token_list)
		return (0);
	if (!token_list->next)
		return (syntax_error(NULL, last_status));
	if (token_list->next->type == IO_NUMBER)
		token_list->next->type = WORD;
	if (token_list->next->type != WORD
		&& token_list->next->type != ASSIGNMENT_WORD)
		return (syntax_error(token_list->next, last_status));
	return (1);
}

int	check_io_num(t_token *token_list)
{
	if (!token_list)
		return (0);
	if (!token_list->next || !is_redir(token_list->next))
		token_list->type = WORD;
	return (1);
}

int	check_syntax(t_token *token_list, int *last_status)
{
	t_token	*tmp;
	int		count;
	int		ret;

	tmp = token_list;
	count = 0;
	ret = 1;
	while (tmp)
	{
		if (tmp->type == PIPE)
			ret = check_pipe(tmp, count, last_status);
		else if (is_redir(tmp))
			ret = check_redir(tmp, last_status);
		else if (tmp->type == IO_NUMBER)
			ret = check_io_num(tmp);
		if (!ret)
			return (0);
		tmp = tmp->next;
		count++;
	}
	return (1);
}
