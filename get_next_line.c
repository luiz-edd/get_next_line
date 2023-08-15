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

char	*find_nl(char **line, char **s_buffer, int fd, ssize_t c_read)
{
	char	*aux_str;
	size_t	nl_index;

	while (!ft_strchr(*s_buffer, '\n') && c_read > 0)
	{
		*line = ft_strjoin(*line, *s_buffer);
		c_read = read(fd, *s_buffer, BUFFER_SIZE);
		*(*s_buffer + c_read) = '\0';
	}
	if (ft_strchr(*s_buffer, '\n') != NULL && c_read > 0)
	{
		nl_index = ft_strlen(*s_buffer) - ft_strlen(ft_strchr(*s_buffer, '\n'));
		aux_str = ft_substr(*s_buffer, 0, nl_index + 1);
		*line = ft_strjoin(*line, aux_str);
		*s_buffer = ft_strdup(*s_buffer + (nl_index + 1));
		return (*line);
	}
	else if (c_read == 0 && (*s_buffer == NULL || **s_buffer == '\0'))
		return (*line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*s_buffer;
	ssize_t		c_read;

	if (fd == ERROR_CODE || BUFFER_SIZE <= 0 || fd > FD_LIMIT)
		return (NULL);
	line = ft_strdup("");
	if (s_buffer == NULL)
	{
		s_buffer = (char *)malloc(BUFFER_SIZE + NULL_BYTE);
		if (s_buffer == NULL || line == NULL)
			return (NULL);
		c_read = read(fd, s_buffer, BUFFER_SIZE);
		*(s_buffer + c_read) = '\0';
	}
	else
		c_read = ft_strlen(s_buffer);
	return (find_nl(&line, &s_buffer, fd, c_read));
}
