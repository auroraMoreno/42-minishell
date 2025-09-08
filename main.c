/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:27:26 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 11:29:42 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signals_main(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_check_gsignal(t_data *data)
{
	if (g_signal != 0)
	{
		data->exit_status = g_signal;
		g_signal = 0;
	}
}

void	ft_exit_eof(int exit_status, t_data *data)
{
	ft_free_all(data, data->cmd_list);
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(exit_status);
}

void	ft_run_shell(t_data *data)
{
	int	exit_status;

	while (1)
	{
		ft_signals_main();
		data->cmd_line = readline(data->prompt);
		ft_check_gsignal(data);
		if (!data->cmd_line)
		{
			exit_status = data->exit_status;
			ft_exit_eof(exit_status, data);
		}
		add_history(data->cmd_line);
		data->cmd_list = parse_input(data->cmd_line);
		ft_executer(data->cmd_list, data);
		if (data->cmd_list)
		{
			free_cmds(data->cmd_list, NULL);
			data->cmd_list = NULL;
		}
		if (data->cmd_line)
			free(data->cmd_line);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_init_data(data, env);
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	ft_run_shell(data);
	ft_free_all(data, data->cmd_list);
	return (data->exit_status);
}
