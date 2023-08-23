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
	char		*line;

	if (fd == ERROR_CODE || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_read_file(&s_buffer, fd);
	if (line == NULL || s_buffer == NULL || *s_buffer == '\0')
		return (ft_free_all(s_buffer, line, NULL));
	ft_update_line_buffer(&line, &s_buffer);
	return (line);
}

char	*ft_read_file(char **s_buffer, int fd)
{
	ssize_t	bytes_read;
	char	*local_buffer;
	char	*temp;

	bytes_read = 1;
	local_buffer = (char *)malloc(BUFFER_SIZE + NULL_BYTE);
	if (*s_buffer == NULL)
		*s_buffer = ft_strdup("");
	if (local_buffer == NULL || *s_buffer == NULL)
		return (ft_free_all(*s_buffer, local_buffer, NULL));
	temp = *s_buffer;
	while (bytes_read != 0 || !ft_strchr(*s_buffer, '\n'))
	{
		bytes_read = read(fd, local_buffer, BUFFER_SIZE);
		if (bytes_read == ERROR_CODE)
			return (ft_free_all(local_buffer, *s_buffer, NULL));
		if (bytes_read == 0)
			local_buffer[bytes_read] = '\0';
		*s_buffer = ft_strjoin(temp, local_buffer);
		if (*s_buffer == NULL)
			return (ft_free_all(temp, local_buffer, NULL));
		ft_free_all(temp, NULL, NULL);
	}
	ft_free_all(local_buffer, NULL, NULL);
	return (ft_strdup(*s_buffer));
}

void	*ft_update_line_buffer(char **line, char **s_buffer)
{
	char	*nl_byte;
	size_t	nl_index;
	char	*temp;

	nl_byte = ft_strchr(*line, '\n');
	if (nl_byte == NULL)
		return (ft_free_all(*s_buffer, NULL, NULL));
	nl_index = ft_strlen(nl_byte) - ft_strlen(*line);
	temp = *s_buffer;
	*s_buffer = ft_strdup(nl_byte);
	if (*s_buffer == NULL)
		return (ft_free_all(*line, *s_buffer, temp));
	*(*line + nl_index + 1) = '\0';
	return (ft_free_all(temp, NULL, NULL));
}

void	*ft_free_all(char *str1, char *str2, char *str3)
{
	if (str1 != NULL)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2 != NULL)
	{
		free(str2);
		str2 = NULL;
	}
	if (str3 != NULL)
	{
		free(str3);
		str3 = NULL;
	}
	return (NULL);
}
