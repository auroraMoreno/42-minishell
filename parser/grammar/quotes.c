/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:24:48 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 18:24:50 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	str_is_quoted(char *token_value)
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

char	*copy_str(char *str)
{
	if (!str)
		return (NULL);
	if (!*str)
		return (ft_strdup(""));
	else
		return (ft_strdup(str));
}
