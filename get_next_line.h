/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:39:11 by leduard2          #+#    #+#             */
/*   Updated: 2023/08/11 21:23:19 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

# define NULL_BYTE 1
# define NL_BYTE 1
# define ERROR_CODE -1
# define NL_BYTE 1
# define FD_LIMIT 1024
# define TRUE 1
# define FALSE 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	ft_strlen(const char *s);
void	*ft_free_return_null(char **str);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char *s);
char	*get_next_line(int fd);
void	ft_read_file(char **s_buffer, char **line, int fd, int *end_of_file);
void	ft_update_line(char **s_bufer, char **line);
void	ft_update_s_buffer(char **s_bufer, char **line);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif