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

char	*get_next_line(int fd)
{
	static char	*s_buffer;
	static int	s_end_of_file;
	char		*line;
	size_t		i;

	i = 0;
	if (fd == ERROR_CODE || BUFFER_SIZE <= 0)
		return (NULL);
	if (s_buffer == NULL)
	{
		s_buffer = (char *)malloc(BUFFER_SIZE + NULL_BYTE);
		if (s_buffer == NULL)
			return (NULL);
		while (i < BUFFER_SIZE + NULL_BYTE)
			s_buffer[i++] = 0;
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
	if (ft_strlen(*s_buffer))
		ft_update_line(s_buffer, line);
	while (!ft_strchr(*s_buffer, '\n') || **s_buffer == '\0')
	{
		bytes_read = read(fd, *s_buffer, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			if (*s_end_of_file == TRUE)
			{
				ft_free_return_null(line);
				ft_free_return_null(s_buffer);
			}
			else
				*s_end_of_file = TRUE;
			return ;
		}
		*(*s_buffer + bytes_read) = '\0';
		ft_update_line(s_buffer, line);
	}
	if (!ft_strchr(*line, '\n'))
		ft_update_line(s_buffer, line);
	ft_update_s_buffer(s_buffer, line);
}

void	ft_update_line(char **s_buffer, char **line)
{
	char	*aux1;
	char	*aux2;
	size_t	nl_index;

	aux1 = *line;
	if (!ft_strchr(*s_buffer, '\n') || **s_buffer == '\0')
		*line = ft_strjoin(*line, *s_buffer);
	else
	{
		nl_index = ft_strlen(*s_buffer) - ft_strlen(ft_strchr(*s_buffer, '\n'));
		aux2 = ft_substr(*s_buffer, 0, nl_index + NL_BYTE);
		if (aux2 == NULL)
			return ((void)ft_free_return_null(line));
		*line = ft_strjoin(*line, aux2);
		ft_free_return_null(&aux2);
	}
	ft_free_return_null(&aux1);
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
		return (void)(ft_free_return_null(line));
	while (aux[i])
	{
		*(*s_buffer + i) = aux[i];
		i++;
	}
	*(*s_buffer + i) = '\0';
	free(aux);
}

void	*ft_free_return_null(char **str)
{
	if (str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}
