/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:46:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 22:06:32 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_file(char *str)
{
	char	*file_name;
	int		fd;
	int		i;
	char	*nbr;

	i = 0;
	while (i < 100000)
	{
		nbr = ft_itoa(i);
		file_name = ft_strjoin("/tmp/.heredoc_", nbr);
		free(nbr);
		if (access(file_name, F_OK))
			break ;
		free(file_name);
		i++;
	}
	fd = open(file_name, O_CREAT | O_RDWR, 0644);
	write(fd, str, ft_strlen(str));
	close(fd);
	return (file_name);
}

char	*exec_heredoc(char *key_word, t_data *data)
{
	char	*input;
	char	*input_x;
	char	*str;
	char	*aux;
	char	*prompt;

	str = ft_calloc(1, 1);
	prompt = ">";
	while (1)
	{
		input = readline(prompt);
		if (input == NULL || ft_strcmp(input, key_word) == 0)
			break ;
		input_x = expand_and_rem_quotes(input, data->env, &(data->exit_status));
		aux = ft_strjoin(str, input_x);
		free(str);
		str = aux;
		aux = ft_strjoin(str, "\n");
		free(str);
		str = aux;
		free(input);
		free(input_x);
	}
	aux = str;
	str = create_file(str);
	return (free(aux), str);
}

char	*ft_heredoc(char *delimitter, t_data *data)
{
	char	*str;
	int		pipefd[2];
	pid_t	id;

	pipe(pipefd);
	id = fork();
	if (id == 0)
	{
		close(pipefd[0]);
		signal(SIGINT, SIG_DFL);
		str = exec_heredoc(delimitter, data);
		ft_putstr_fd(str, pipefd[1]);
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
	close(pipefd[1]);
	signal(SIGINT, SIG_IGN);
	wait(NULL);
	str = get_next_line(pipefd[0]);
	close(pipefd[0]);
	signal(SIGINT, ft_handle_sigint);
	if (str == NULL)
		str = ft_strdup("/dev/null");
	return (str);
}
