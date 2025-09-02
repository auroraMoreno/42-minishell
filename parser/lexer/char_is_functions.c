#include "../minishell.h"

int	is_space(char c)
{
	char	*space;
	int		i;

	space = " \t\r\n\v\f";
	i = 0;
	while (space[i])
	{
		if (c == space[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_quote(char c)
{
	char	*quote;
	int		i;

	quote = "\"\'";
	i = 0;
	while (quote[i])
	{
		if (c == quote[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_operator(char c)
{
	char	*operator;
	int		i;

	operator = ">|<";
	i = 0;
	while (operator[i])
	{
		if (c == operator[i])
			return (1);
		i++;
	}
	return (0);
}