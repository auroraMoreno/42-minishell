/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:42:05 by aumoreno          #+#    #+#             */
/*   Updated: 2025/08/28 23:39:34 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// << 

ssize_t ft_read_bytes(int fd, char **buffer, char **content, int buffer_size)
{
	ssize_t bytes;
	char *aux;

	bytes = read(fd, buffer, buffer_size);
	while(bytes > 0)
	{
		buffer[bytes] = '\0'; //vamos poniendo el null a medida que va leyendo más 
		aux = ft_strjoin(content, buffer);
		free(content);
		content = aux;
		if(!content)
		{
			free(buffer);
			return(0);
		}
		bytes = read(fd, buffer, buffer_size);
	}
	return (bytes);
}

char *ft_read_content_heredoc(int fd)
{
	char *content; 
	char *buff;
	ssize_t bytes_read; 
	int buffer_size = 10;

	content = ft_calloc(1,1);
	if(!content)
		return (0);
	buff = ft_calloc(buffer_size + 1, 1);
	if(!buff)
	{
		free(content);
		return (0);
	}
	bytes_read = ft_read_bytes(fd, &buff, &content, buffer_size);
	free(buff);
	if(bytes_read == -1)
	{
		free(content);
		return (0);
	}
	return (content);
}


char *ft_handle_heredoc(char *delimitter)
{
	char *line;
	char *content;
	char *aux;
	
	content = ft_calloc(1,1);
	
	while(1)
	{
		line = readline(">");
		if(!line || ft_strcmp(line, delimitter))
			break;
		aux = ft_strjoin(content, line);
		free(content);
		content = ft_strjoin(aux, "\n");
		free(aux);
		free(line);
	}
	if(line)
		free(line);
	return (content);
}

char *ft_heredoc(char *delimitter)
{
    char *content;
    int	fds[2];
	pid_t process_id;
	
	pipe(fds);
	process_id = fork();
	if(process_id == 0)
	{
		close(fds[0]); //el hijo solo va a escribir, cerramos lectura
		signal(SIGINT, SIG_DFL);
		content = ft_handle_heredoc(delimitter); //TO-DO
		// escribimos el contenido en el extremo escritura de la pipe
		ft_putstr_fd(content, fds[1]); 
		close(fds[1]); //cerramos porq ya no necesitamos 
		exit(EXIT_SUCCESS); //modificar esto porq no me gusta, ver si se puede exit code o algo
	}
	close(fds[1]); //el padre solo lee
	signal(SIGINT, SIG_IGN);
	//esperar a que el hijo acabe
	wait(NULL); //ver si puedo hacer waitpid 
	//leemos lo que ha escrito el hijo
	content = ft_read_content_heredoc(fds[0]); //check errors ? 
	close(fds[0]);
	signal(SIGINT, ft_handle_sigint);
	
	if(!content)
		content = ft_strdup(""); //preguntar a jorge si esto guay
	return (content);
}