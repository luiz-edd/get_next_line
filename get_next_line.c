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

void	update_s_buffer(char **s_buffer, size_t nl_index)
{
	int		i;
	char	*new_content;

	new_content = ft_strdup(*s_buffer + (nl_index + NL_BYTE));
	i = 0;
	while (new_content[i])
	{
		*(*s_buffer + i) = new_content[i];
		i++;
	}
	*(*s_buffer + i) = '\0';
	free(new_content);
}

char	*find_nl(char **s_buffer, int fd, ssize_t c_read)
{
	char	*aux_str;
	size_t	nl_index;
	char	*line;
	char	*aux_line;

	// inicialize line
	line = ft_strdup("");
	// search for a \n in the buffer, if not found, add s_buffer to the line
	// and read the next content of file
	// if (*s_buffer == NULL)
	// {
	// 	return (NULL);
	// }
	while ((!ft_strchr(*s_buffer, '\n') && c_read > 0))
	{
		aux_str = line;
		line = ft_strjoin(line, *s_buffer);
		free(aux_str);
		c_read = read(fd, *s_buffer, BUFFER_SIZE);
		*(*s_buffer + c_read) = '\0';
	}
	// \n founded or end of file is achive,
	if (ft_strchr(*s_buffer, '\n') != NULL && c_read > 0)
	{
		// find \n index inside s_buffer
		nl_index = ft_strlen(*s_buffer) - (ft_strlen(ft_strchr(*s_buffer,
					'\n')));
		// create a temporary str holding all the content including and before \n
		aux_str = ft_substr(*s_buffer, 0, nl_index + 1);
		// adding the temporary str to the line
		// ---------------------------------------- TRY TO FREE AUX_STR
		aux_line = line;
		line = ft_strjoin(line, aux_str);
		free(aux_str);
		free(aux_line);
		// removing all the content before \n in s_buffer
		update_s_buffer(s_buffer, nl_index);
		if (line == NULL)
		{
			// free(line);
			return (NULL);
		}
		return (line);
	}
	else if (c_read == 0)
	{
		// free(*s_buffer);
		// free(line);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*s_buffer;
	ssize_t		c_read;

	if (fd == ERROR_CODE || BUFFER_SIZE <= 0 || fd > FD_LIMIT)
		return (NULL);
	// inicialize s_buffer if its the first time beeing called
	if (s_buffer == NULL)
	{
		s_buffer = (char *)malloc(BUFFER_SIZE + NULL_BYTE);
		if (s_buffer == NULL)
		{
			// free(s_buffer);
			return (NULL);
		}
		// add the content of the file inside buffer
		c_read = read(fd, s_buffer, BUFFER_SIZE);
		if (c_read == 0)
		{
			// free(s_buffer);
			return (NULL);
		}
		*(s_buffer + c_read) = '\0';
	}
	else if (*s_buffer == '\0')
	{
		c_read = read(fd, s_buffer, BUFFER_SIZE);
	}
	else
	{
		c_read = ft_strlen(s_buffer);
	}
	return (find_nl(&s_buffer, fd, c_read));
}
