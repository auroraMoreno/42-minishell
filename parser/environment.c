#include "../minishell.h"

void	free_env_list(t_env **head)
{
	t_env	*tmp;

	if (!head)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp->key)
			free (tmp->key);
		if (tmp->value)
			free (tmp->value);
		free (tmp);
	}
	*head = NULL;
	return ;
}

t_env	*env_fail(t_env **head, t_env *node)
{
	if (node)
	{
		if (node->key)
			free (node->key);
		if (node->value)
			free (node->value);
		free (node);
	}
	free_env_list(head);
	return (NULL);
}

int	set_var(t_env *node, char *envp)
{
	size_t	i;
	size_t	len;

	if (!node || !envp)
		return (0);
	i = 0;
	len = ft_strlen(envp);
	while (envp[i] && envp[i] != '=')
		i++;
	if (i == len)
		return (0);
	node->key = ft_substr(envp, 0, i);
	if (!node->key)
		return (0);
	i++;
	node->value = ft_substr(envp, i, len - i);
	if (!node->value)
	{
		free (node->key);
		return (0);
	}
	node->next = NULL;
	return (1);
}

int	list_vars(t_env **head, t_env *node)
{
	t_env	*tmp;

	if (!head || !node)
		return (0);
	if (!*head)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (1);
}

t_env	*extract_env(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	if (!envp)
		return (NULL);
	head = NULL;
	i = 0;
	while (envp[i])
	{
		node = (t_env *)ft_calloc(1, sizeof(t_env));
		if (!node)
			return (env_fail(&head, NULL));
		if (!set_var(node, envp[i]))
			return (env_fail(&head, node));
		if (!list_vars(&head, node))
			return (env_fail(&head, node));
		i++;
	}
	return (head);
}
