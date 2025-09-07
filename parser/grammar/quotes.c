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

/*t_quote_type type_of_quote(char *token_value)
{
	if (!token_value || !*token_value)
		return (NO_QUOTE);
	while (*token_value)
	{
		if (*token_value == '\'')
			return (SINGLE_QUOTE);
		if (*token_value == '"')
			return (DOUBLE_QUOTE);
		token_value++;
	}
	return (NO_QUOTE);
}*/

/*char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		new_str_len;
	char	*new_str;

	if (!str)
		return (NULL);
	if (!*str)
		return (ft_strdup(""));
	new_str_len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new_str_len++;
	}
	new_str = (char *)ft_calloc(new_str_len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new_str[++j] = str[i];
	}
	new_str[new_str_len] = '\0';
	return (new_str);
}*/

char	*copy_str(char *str)
{
	if (!str)
		return (NULL);
	if (!*str)
		return (ft_strdup(""));
	else
		return (ft_strdup(str));
}
