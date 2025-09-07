#include "../minishell.h"

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

int	handle_quote_char(char c, t_quote_type *quote_type)
{
	if (*quote_type != NO_QUOTE)
	{
		if ((*quote_type == SINGLE_QUOTE && c == '\'')
			|| (*quote_type == DOUBLE_QUOTE && c == '"'))
		{
			*quote_type = NO_QUOTE;
			return (0);
		}
		else
			return (1);
	}
	else
	{
		if (c == '\'')
			*quote_type = SINGLE_QUOTE;
		else
			*quote_type = DOUBLE_QUOTE;
		return (0);
	}
}

int	handle_dollar_copy(char *in, int *i, char *out, t_expand_ctx *ctx)
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
			return (-1);
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

t_expand_ctx	gain_context(t_env *env, int *last_status, t_quote_type *quote_type)
{
	t_expand_ctx	ctx;

	*quote_type = NO_QUOTE;
	ctx.last_status = last_status;
	ctx.env = env;
	return (ctx);
}

char	*craft_out(char *in, char *out, t_env *env, int *last_status)
{
	int				i;
	int				o;
	t_quote_type	quote_type;
	t_expand_ctx	ctx;
	int				written;

	i = -1;
	o = 0;
	ctx = gain_context(env, last_status, &quote_type);
	while (in[++i])
	{
		if (is_quote(in[i]) && handle_quote_char(in[i], &quote_type))
			out[o++] = in[i];
		else if (in[i] == '$' && quote_type != SINGLE_QUOTE)
		{
			written = handle_dollar_copy(in, &i, out + o, &ctx);
			if (written < 0)
				return (NULL);
			o += written;
		}
		else if (!is_quote(in[i]))
			out[o++] = in[i];
	}
	out[o] = '\0';
	return (out);
}
