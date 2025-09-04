#include "../minishell.h"

int	check_syntax(t_token *token_list)
{
	t_token	*tmp;
	int		i;

	tmp = token_list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			check_pipe(token_list, i);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
		i++;
	}
	if (tmp->type == PIPE || is_redir(tmp))
		return (syntax_error(token_list));
	return (1);
}