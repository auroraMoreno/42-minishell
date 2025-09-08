/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:03:48 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 09:14:54 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	ft_atoi_exit_code(char *str_code)
{
	int				i;
	int				sign;
	unsigned long	res;

	res = 0;
	sign = 1;
	i = 0;
	while (str_code[i] == 32 || (str_code[i] >= 9 && str_code[i] <= 13))
		i++;
	if (str_code[i] == '-' || str_code[i] == '+')
	{
		if (str_code[i] == '-')
			sign = -1;
		i++;
	}
	while (str_code[i] >= 48 && str_code[i] <= 57)
	{
		res = res * 10 + (str_code[i] - 48);
		i++;
	}
	return ((long)res * sign % 256);
}

int	ft_exit(t_cmd *cmd, t_data *data)
{
	int	exit_code;
	int	len;

	len = argv_len(cmd->argv);
	if (len > 2)
		return (ft_formatted_error("too many arguments", "-bash: exit ", data));
	if (len == 1)
	{
		exit_code = data->exit_status;
		ft_free_all(data, data->cmd_list);
		exit(exit_code);
	}
	exit_code = ft_atoi_exit_code(cmd->argv[1]);
	if (exit_code == -1)
	{
		ft_formatted_error("invalid argument", "-bash: exit", data);
		ft_free_all(data, data->cmd_list);
	}
	ft_free_all(data, data->cmd_list);
	exit(exit_code);
	return (0);
}
