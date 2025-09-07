#include "../minishell.h"


////EXPANDER UTILS
//////////////////
int	potential_var(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

size_t	scan_var_name(char *in, int pos)
{
	size_t	len;

	if (!in[pos])
		return (0);
	if (!ft_isalpha(in[pos]) && in[pos] != '_')
		return (0);
	(pos)++;
	len = 1;
	while (ft_isalnum(in[pos]) || in[pos] == '_')
	{
		len++;
		(pos)++;
	}
	return (len);
}

t_env	*find_var(char *var, t_env *env, size_t len)
{
	t_env	*match;

	match = env;
	while (match)
	{
		if (match->key
			&& !ft_strncmp(match->key, var, len)
			&& match->key[len] == '\0')
			return (match);
		match = match->next;
	}
	return (NULL);
}

//////////////////
////EXPANDER UTILS



////EXPANSION LENGTH
//////////////////

size_t	var_len(char *in, int *pos, t_env *env)
{
	size_t	len;
	t_env	*var_in_env;

	len = scan_var_name(in, *pos);
	if (!len)
		return (0);
	var_in_env = find_var(in + *pos, env, len);
	*pos += (int)len;
	if (!var_in_env || !var_in_env->value)
		return (0);
	return (ft_strlen(var_in_env->value));
}

size_t	digits_len(int nbr)
{
	size_t			len;
	unsigned int	n;

	len = 1;
	if (nbr < 0)
	{
		len++;
		n = (unsigned int)(-(long long)nbr);
	}
	else
		n = (unsigned int)nbr;
	while (n >= 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	update_quote_state(char c, bool *in_quote, t_quote_type *quote_type, size_t *len)
{
	if (*in_quote)
	{
		if ((*quote_type == SINGLE_QUOTE && c == '\'')
			|| (*quote_type == DOUBLE_QUOTE && c == '"'))
		{
			*in_quote = false;
			*quote_type = NO_QUOTE;
		}
		else
			(*len)++;
	}
	else
	{
		*in_quote = true;
		if (c == '\'')
			*quote_type = SINGLE_QUOTE;
		else
			*quote_type = DOUBLE_QUOTE;
	}
	return ;
}

size_t	handle_dollar_len(char *in, int *i, t_env *env, int *last_status)
{
	size_t	len;

	if (!in[*i + 1] || !potential_var(in[*i + 1]))
		return (1);
	(*i)++;
	if (in[*i] == '?')
		return (digits_len(*last_status));
	len = var_len(in, i, env);
	(*i)--;
	return (len);
}

size_t	expansion_len(char *in, t_env *env, int *last_status)
{
	int				i;
	bool			in_quote;
	t_quote_type	quote_type;
	size_t			len;

	i = 0;
	in_quote = false;
	quote_type = NO_QUOTE;
	len = 0;
	while (in[i])
	{
		if (is_quote(in[i]))
			update_quote_state(in[i], &in_quote, &quote_type, &len);
		else if (in[i] == '$' && quote_type != SINGLE_QUOTE)
			len += handle_dollar_len(in, &i, env, last_status);
		else
			len++;
		i++;
	}
	return (len);
}

//////////////////
////EXPANSION LENGTH




//// MAKE EXPANSION
//////////////////

void	expand_laststatus(char *out, int *o, int *last_status)
{
	int		i;
	char	*status;

	status = ft_itoa(*last_status);
	if (!status)
		return ;
	i = 0;
	while (status[i])
	{
		out[*o] = status[i];
		i++;
		(*o)++;
	}
	free (status);
	return ;
}

int	expand_var(char *in, int *i, char *out, t_env *env)
{
	size_t	len;
	t_env	*var_in_env;
	int		j;
	char	*value;

	len = scan_var_name(in, *i);
	if (!len)
		return (0);
	var_in_env = find_var(in + *i, env, len);
	*i += (int)len;
	if (!var_in_env || !var_in_env->value)
		value = "";
	else
		value = var_in_env->value;
	j = 0;
	while (value[j])
	{
		out[j] = value[j];
		j++;
	}
	return (j);
}

int	handle_quote_char(char c, bool *in_quote, t_quote_type *quote_type)
{
	if (*in_quote)
	{
		if ((*quote_type == SINGLE_QUOTE && c == '\'')
			|| (*quote_type == DOUBLE_QUOTE && c == '"'))
		{
			*in_quote = false;
			*quote_type = NO_QUOTE;
			return (0);
		}
		else
			return (1);
	}
	else
	{
		*in_quote = true;
		if (c == '\'')
			*quote_type = SINGLE_QUOTE;
		else
			*quote_type = DOUBLE_QUOTE;
		return (0);
	}
}

static int	handle_dollar_copy(char *in, int *i, char *out, t_expand_ctx *ctx)
{
	int		written;
	char	*status_val;
	int		j;

	if (!in[*i + 1] || !potential_var(in[*i + 1]))
	{
		out[0] = '$';
		return (1);
	}
	(*i)++;
	if (in[*i] == '?')
	{
		status_val = ft_itoa(*(ctx->last_status));
		if (!status_val)
			return (0);
		j = -1;
		while (status_val[++j])
			out[j] = status_val[j];
		free (status_val);
		return (j);
	}
	written = expand_var(in, i, out, ctx->env);
	(*i)--;
	return (written);
}


char	*craft_out(char *in, char *out, t_env *env, int *last_status)
{
	int				i;
	int				o;
	bool			in_quote;
	t_quote_type	quote_type;
	t_expand_ctx	ctx;

	i = 0;
	o = 0;
	in_quote = false;
	quote_type = NO_QUOTE;
	ctx.last_status = last_status;
	ctx.env = env;
	while (in[i])
	{
		if (is_quote(in[i]) && handle_quote_char(in[i], &in_quote, &quote_type))
			out[o++] = in[i];
		else if (in[i] == '$' && quote_type != SINGLE_QUOTE)
			o += handle_dollar_copy(in, &i, out + o, &ctx);
		else
			out[o++] = in[i];
		i++;
	}
	out[o] = '\0';
	return (out);
}

//////////////////
//// MAKE EXPANSION


////EXPANDER MAIN
//////////////////

char	*expand_and_rem_quotes(char *in, t_env *env, int *last_status)
{
	size_t	out_len;
	char	*out;

	if (!in || !last_status)
		return (NULL);
	out_len = expansion_len(in, env, last_status);
	out = (char *)ft_calloc(out_len + 1, sizeof(char));
	if (!out)
		return (NULL);
	craft_out(in, out, env, last_status);
	return (out);
}

int	expand_argv(char **argv, t_env *env, int *last_status)
{
	int		i;
	char	*new;

	if (!argv || !*argv)
		return (1);
	if (!last_status)
		return (0);
	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '$') || str_is_quoted(argv[i]))
		{
			new = expand_and_rem_quotes(argv[i], env, last_status);
			if (!new)
				return (0);
			free (argv[i]);
			argv[i] = new;
		}
		i++;
	}
	return (1);
}

int	expand_asgns(t_assign *assgns, t_env *env, int *last_status)
{
	t_assign	*tmp;
	char		*new;

	tmp = assgns;
	while (tmp)
	{
		if (tmp->value
			&& (ft_strchr(tmp->value, '$') || str_is_quoted(tmp->value)))
		{
			new = expand_and_rem_quotes(tmp->value, env, last_status);
			if (!new)
				return (0);
			free (tmp->value);
			tmp->value = new;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	expand_redir(t_redir *redirs, t_env *env, int *last_status)
{
	t_redir	*tmp;
	char	*new;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->target && tmp->redir_type != R_HEREDOC
			&& (ft_strchr(tmp->target, '$') || str_is_quoted(tmp->target)))
		{
			new = expand_and_rem_quotes(tmp->target, env, last_status);
			if (!new)
				return (0);
			free (tmp->target);
			tmp->target = new;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	expand_cmds(t_cmd *cmd_list, t_env *env, int *last_status)
{
	t_cmd	*tmp;

	if (!cmd_list || !last_status)
		return (0);
	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->argv)
		{
			if (!expand_argv(tmp->argv, env, last_status))
				return (0);
		}
		if (tmp->assignments)
		{
			if (!expand_asgns(tmp->assignments, env, last_status))
				return (0);
		}
		if (tmp->redirs)
		{
			if (!expand_redir(tmp->redirs, env, last_status))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

//////////////////
////EXPANDER MAIN