#include "../minishell.h"

int	count_pipes(t_token *token_list)
{
	int		i;

	i = 0;
	while (token_list->next)
	{
		if (token_list->type == PIPE)
			i++;
		token_list = token_list->next;
	}
	if (token_list->value == '|')
		i++;
	return (i);
}

int	check_pipes(t_token *token_list, int pipes_nbr, int **pipes_pos)
{
	int	i;

	pipes_pos = (int *)malloc(pipes_nbr * sizeof(int));
	if (!pipes_pos)
		return (0);
	i = 0;
	while (token_list->next)
	{
		if (token_list->type == PIPE)
			*pipes_pos++ = i;
		i++;
		token_list = token_list->next;
	}
	if (token_list->value == '|')
		return (0);
	i = 0;
	if (*pipes_pos[i] == 0)
		return (0);
	while (++i < pipes_nbr)
	{
		if (*pipes_pos[i] == *pipes_pos[i] + 1)
			return (0);
	}
	return (1);
}

void	detect_cmds(t_token *token_list, int cmds_nbr, int **cmds_pos)
{
	int	pipes_nbr;
	int	*pipes_pos;
	int	i;

	cmds_nbr = 0;
	pipes_nbr = count_pipes(token_list);
	if (pipes_nbr > 0)
	{
		if (!check_pipes(token_list, pipes_nbr, &pipes_pos))
			return ;
	}
	cmds_nbr = (1 + pipes_nbr);
	cmds_pos = (int *)malloc(cmds_nbr * sizeof(int));
	if (!cmds_pos)
		cmds_pos = NULL;
	i = 0;
	while (token_list->next)
	{
		if (pipes_nbr)
			*cmds_pos++ = pipes_pos++;
		token_list = token_list->next;
		i++;
	}
	*cmds_pos = i;
	free (pipes_pos);
}

t_cmd	*tokens_to_cmds(t_token *token_list)
{
	t_cmd	*cmd_list;
	t_cmd	*cmd_node;
	int		cmds_nbr;
	int		*cmds_pos;
	int		i;

	if (!token_list)
		return (NULL);
	detect_cmds(token_list, &cmds_nbr, &cmds_pos);
	if (!cmds_nbr || !cmds_pos)
		return (NULL);
	cmd_list = (t_cmd *)malloc(cmds_nbr * sizeof(t_cmd));
	if (!cmd_list)
		return (NULL);
	i = 0;
	while (cmds_nbr-- > 0)
	{
		cmd_node = (t_cmd *)malloc(sizeof(t_cmd));
		while (i++ < *cmds_pos)
		{
			craft_cmd(token_list, &cmd_node);
			token_list = token_list->next;
		}
		i++;
		cmds_pos++;
	}
}
