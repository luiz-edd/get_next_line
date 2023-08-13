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

void	find_nl(char **line, char **s_buffer)
{
	ssize_t	c_read;
	char *aux;

	if (!*line)
		ft_strdup("");
	c_read = read(fd, s_buffer, BUFFER_SIZE);
	while (!ft_strchr(c_read, '\n') && c_read > 0)
	{
		aux = *line;
		*line = ft_strjoin(*line, s_buffer);
		free(aux);
		c_read = read(fd, s_buffer, BUFFER_SIZE);
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*s_buffer;

	if (fd == ERROR_CODE || BUFFER_SIZE <= 0 || fd > FD_LIMIT)
		return (NULL);
	s_buffer = (char *)malloc(BUFFER_SIZE + NULL_BYTE);
	if (s_buffer == NULL)
		return (NULL);
	find_nl(&line, &s_buffer);
}

// "Lorem ipsum dolor sit amet, consectetur adipiscing elit. \n
//  Duis lacus eros, interdum sit amet rutrum a, malesuada quis orci.\n
//  Interdum et malesuada fames ac ante ipsum primis in faucibus.\n
//  Ut id dignissim odio, a vulputate metus. Donec sed nibh posuere, \n
//  molestie velit sit amet, \n
//  laoreet diam.\n
//  Etiam \n
//  a quam id quam \n
//  sagittis \n
//  dignissim. Nunc ac lorem enim. Praesent tincidunt nibh vitae tortor sollicitudin sagittis. Aliquam erat volutpat. Fusce sit amet congue orci."
