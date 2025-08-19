#include "../minishell.h"

t_cmd	*tokens_to_cmds(t_token *token_list)
{
	t_cmd	*cmd_list;
	t_cmd	*cmd_node;
	t_token	*tmp;
	int		i;

	if (!token_list)
		return (NULL);
	i = 1;
	tmp = token_list;
	while (tmp->next != NULL)
	{
		cmd_node = new_cmd(tmp);
		add_cmd(&cmd_list, cmd_node);
		tmp = tmp->next;
	}
	cmd_list = (t_cmd *)malloc(i * sizeof(t_cmd));
}
