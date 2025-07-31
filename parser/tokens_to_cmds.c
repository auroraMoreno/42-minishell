#include "../minishell.h"

t_cmd	*tokens_to_cmds(t_token *token_list)
{
	t_cmd	*cmd_list;
	t_token	*tmp;
	int		i;

	if (!token_list)
		return (NULL);
	i = 1;
	tmp = token_list;
	while (tmp->next != NULL)
	{
		if (tmp->type == PIPE)
		i++;
		tmp	= tmp->next;
	}
	cmd_list = (t_cmd *)malloc(i * sizeof(t_cmd));
}
