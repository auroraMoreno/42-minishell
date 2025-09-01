/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:25:23 by aumoreno          #+#    #+#             */
/*   Updated: 2025/09/01 10:47:21 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_update_content(char *content, t_data *data)
{
    
}

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


//review this method!! 

void ft_remove_heredoc_lines(int from, t_data *data)
{
    char **extra_heredoc;
    size_t len;
    int i;
    
    if(!data->heredoc_content)
        return; //TO-DO: error managemente and exit code appropiatly
    len = ft_get_array_size(data->heredoc_content);
    if(from > len)
    {
        //FREE
        //return
    }
    extra_heredoc = malloc(sizeof(char *) * (len - from + 1));
    if(!extra_heredoc)
        ft_exit();
    
    i = 0;
    while(from < len && data->heredoc_content[from])
    {
        extra_heredoc[i] = ft_strdup(data->heredoc_content[from]); //desde la linea que ya no es heredoc
        if(!extra_heredoc[i])
        {
            //FREE
            ft_exit();
        }
        from++;
        i++;
    }

    extra_heredoc[i] = NULL;

    //free
    data->heredoc_content = extra_heredoc;
}