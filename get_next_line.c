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
	char		*line;
	static char	*s_buffer;
	ssize_t		c_read;

	if (fd == ERROR_CODE || BUFFER_SIZE <= 0 || fd > FD_LIMIT)
		return (NULL);
	s_buffer = (char *)malloc(BUFFER_SIZE + NULL_BYTE);
	if (s_buffer == NULL)
		return (NULL);
	c_read = read(fd, s_buffer, BUFFER_SIZE);
	
}
