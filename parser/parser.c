/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:41:29 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 20:14:05 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*lexer(char *cmd, int *last_status)
{
	char	**tokens;
	t_token	*token_list;

	tokens = input_to_tokens(cmd);
	if (!tokens || !*tokens)
	{
		if (tokens)
			free_matrix(tokens);
		return (NULL);
	}
	token_list = tokens_in_list(tokens);
	free_matrix(tokens);
	if (!token_list)
		return (NULL);
	if (!check_syntax(token_list, last_status))
	{
		free_token_list(token_list);
		return (NULL);
	}
	return (token_list);
}

t_cmd	*grammar(t_token	*token_list, t_data *data)
{
	t_cmd	*cmd_list;

	cmd_list = tokens_to_cmds(token_list, data);
	free_token_list(token_list);
	if (!cmd_list)
		return (NULL);
	if (!expand_cmds(cmd_list, data->env, &(data->exit_status)))
		return (free_cmds(cmd_list, NULL));
	return (cmd_list);
}

t_cmd	*parse_input(t_data *data, int *last_status)
{
	t_token	*token_list;
	t_cmd	*cmd_list;

	token_list = lexer(data->cmd_line, last_status);
	if (!token_list)
		return (NULL);
	cmd_list = grammar(token_list, data);
	if (!cmd_list)
		return (NULL);
	return (cmd_list);
}
