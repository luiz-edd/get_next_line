/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:35:57 by leduard2          #+#    #+#             */
/*   Updated: 2023/08/11 16:56:41 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//return 0 if the function din't find '\n' in the *str
size_t	ft_nl_index(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	const char	*rest;
	char		*line;
	char		*buffer;
	size_t		chars_read;

	if (rest == NULL)
	{
		rest = ft_strldup("");
	}
	line = rest;
	buffer = (char *)malloc(BUFFER_SIZE + NULL_BYTE);
	if (buffer == NULL)
		return (NULL);
	chars_read = read(fd, buffer, BUFFER_SIZE);
	if (chars_read == 0)
	{
		// end of file
	}
	buffer[chars_read] = '\0';
	if (ft_nl_index(buffer))
	{
		buffer[ft_nl_index(buffer)] = '\0';
	}
	ft_strjoin(rest, buffer);
}

int	main(void)
{
	
}