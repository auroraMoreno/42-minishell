#include "../minishell.h"

int	set_assign(t_assign *asgn_wrd, char	*wrd)
{
	size_t	equal_pos;
	size_t	pos_to_end;

	if (!asgn_wrd || !wrd)
		return (0);
	equal_pos = 0;
	while (wrd[equal_pos] && wrd[equal_pos] != '=')
		equal_pos++;
	if (equal_pos == ft_strlen(wrd))
		return (0);
	asgn_wrd->key = ft_substr(wrd, 0, equal_pos++);
	if (!asgn_wrd->key)
		return (0);
	pos_to_end = ft_strlen(wrd) - equal_pos;
	asgn_wrd->value = ft_substr(wrd, equal_pos, pos_to_end);
	if (!asgn_wrd->value)
	{
		free (asgn_wrd->key);
		return (0);
	}
	asgn_wrd->next = NULL;
	return (1);
}

void	append_asgn_node(t_cmd *current_cmd, t_assign *asgn_wrd)
{
	t_assign	*tmp;

	if (!current_cmd->assignments)
		current_cmd->assignments = asgn_wrd;
	else
	{
		tmp = current_cmd->assignments;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = asgn_wrd;
	}
	return ;
}

int	add_asgn_wrd(t_cmd *current_cmd, t_token **token_list, bool *exec_seen)
{
	t_assign	*asgn_wrd;

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
	append_asgn_node(current_cmd, asgn_wrd);
	*token_list = (*token_list)->next;
	return (1);
}
