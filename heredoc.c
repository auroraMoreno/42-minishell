/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno <aumoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:46:57 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/08 00:10:55 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	there_doc(void)
{
	char	*file_name;
	int		i;
	char	*nbr;

	i = 0;
	while (i < 100000)
	{
		nbr = ft_itoa(i);
		file_name = ft_strjoin("/tmp/.heredoc_", nbr);
		free(nbr);
		if (!access(file_name, F_OK))
			unlink(file_name);
		else
			i = -2;
		free(file_name);
		i++;
		if (i == -1)
			break ;
	}
}

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

static char	*exec_heredoc(char *key_word)
{
	char	*input;
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
        
        aux = ft_strjoin(str, input);
        free(str);
        str = aux;
        
        aux = ft_strjoin(str, "\n");
        free(str);
        str = aux;
        
        free(input);
	}
	aux = str;
	str = create_file(str);
	free(aux);
	return (str);
}

char	*heredoc(char *key_word)
{
	char	*str;
	pid_t	id;
	int		pipefd[2];

	pipe(pipefd);
	id = fork();
	if (id == 0)
	{
		close(pipefd[0]);
		signal(SIGINT, SIG_DFL);
		str = exec_heredoc(key_word);
		//printf("CREATE FILE:%s\n", str);
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
