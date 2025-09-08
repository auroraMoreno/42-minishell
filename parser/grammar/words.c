/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:28:12 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 18:28:15 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

bool	check_builtin(char	*exec)
{
	bool	is_builtin;

	if (!ft_strncmp(exec, "echo", ft_strlen("echo") + 1))
		is_builtin = true;
	else if (!ft_strncmp(exec, "cd", ft_strlen("cd") + 1))
		is_builtin = true;
	else if (!ft_strncmp(exec, "pwd", ft_strlen("pwd") + 1))
		is_builtin = true;
	else if (!ft_strncmp(exec, "export", ft_strlen("export") + 1))
		is_builtin = true;
	else if (!ft_strncmp(exec, "unset", ft_strlen("unset") + 1))
		is_builtin = true;
	else if (!ft_strncmp(exec, "env", ft_strlen("env") + 1))
		is_builtin = true;
	else if (!ft_strncmp(exec, "exit", ft_strlen("exit") + 1))
		is_builtin = true;
	else
		is_builtin = false;
	return (is_builtin);
}

int	add_word(t_cmd *current_cmd, t_token **token_list, bool *exec_seen)
{
	char	**tmp;

	if (!current_cmd || !token_list || !*token_list || !exec_seen)
		return (0);
	tmp = push_to_argv(current_cmd->argv, (*token_list)->value);
	if (!tmp)
		return (0);
	current_cmd->argv = tmp;
	if (!*exec_seen)
	{
		current_cmd->is_builtin = check_builtin(current_cmd->argv[0]);
		*exec_seen = true;
	}
	*token_list = (*token_list)->next;
	return (1);
}
