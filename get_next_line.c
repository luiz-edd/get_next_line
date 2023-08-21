/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:35:57 by leduard2          #+#    #+#             */
/*   Updated: 2023/08/11 22:00:20 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// steps logic
// create malloc buffer_size > read file > add content to line
// create malloc buffer_size, make a static pointer to it. > read file,
// if \n not found
// add the content of s_buffer to a line
// update static buffer to have the content after \n,
// verify if the \n is the end of the line
// if \n not found and bytes_read == 0, return (line);

char	*get_next_line(int fd)
{
	static char	*s_buffer;
	static int	s_end_of_file;
	char		*line;

	if (fd == ERROR_CODE || BUFFER_SIZE <= 0 || fd > FD_LIMIT)
		return (NULL);
	if (s_buffer == NULL)
	{
		s_buffer = (char *)ft_calloc(BUFFER_SIZE + NULL_BYTE, 1);
		if (s_buffer == NULL)
			return (NULL);
	}
	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	ft_read_file(&s_buffer, &line, fd, &s_end_of_file);
	return (line);
}

void	ft_read_file(char **s_buffer, char **line, int fd, int *s_end_of_file)
{
	ssize_t	bytes_read;

	if (*line == NULL)
		return ;
	if (!ft_strchr(*s_buffer, '\n') || **s_buffer == '\0')
	{
		bytes_read = read(fd, *s_buffer, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			if (*s_end_of_file == TRUE)
			{
				free(*line);
				*line = NULL;
			}
			else
				*s_end_of_file = TRUE;
			return ;
		}
		*(s_buffer + bytes_read) = '\0';
		ft_update_line(s_buffer, line, FALSE);
		ft_read_file(s_buffer, line, fd, s_end_of_file);
	}
	else
	{
		ft_update_line(s_buffer, line, TRUE);
		ft_update_s_buffer(s_buffer, line);
	}
}

void	ft_update_line(char **s_buffer, char **line, int finded_nl)
{
	char	*aux1;
	char	*aux2;
	size_t	nl_index;

	aux1 = *line;
	if (finded_nl == TRUE)
	{
		nl_index = ft_strlen(*s_buffer) - ft_strlen(ft_strchr(*s_buffer, '\n'));
		aux2 = ft_substr(*s_buffer, 0, nl_index + NL_BYTE);
		if (aux2 == NULL)
		{
			free(*line);
			*line = NULL;
			return ;
		}
		*line = ft_strjoin(*line, aux2);
		free(aux2);
	}
	else
		*line = ft_strjoin(*line, *s_buffer);
	free(aux1);
}

void	ft_update_s_buffer(char **s_buffer, char **line)
{
	size_t	nl_index;
	char	*aux;
	size_t	i;

	nl_index = ft_strlen(*s_buffer) - ft_strlen(ft_strchr(*s_buffer, '\n'));
	aux = ft_strdup(*s_buffer + nl_index + 1);
	i = 0;
	if (aux == NULL)
	{
		free(line);
		*line = NULL;
		return ;
	}
	while (aux[i])
	{
		*(*s_buffer + i) = aux[i];
		i++;
	}
	*(*s_buffer + i) = '\0';
	free(aux);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}