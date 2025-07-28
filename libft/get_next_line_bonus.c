/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:58:32 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/07 17:23:08 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_line_buffer(char *buffer)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static void	buffer_move(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i] != '\0')
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
}

char	*read_to_buffer(int fd, char *buffer, char *temp)
{
	char	buffer_read[BUFFER_SIZE + 1];
	int		read_bytes;
	char	*temp_old;

	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(temp, '\n'))
	{
		read_bytes = read(fd, buffer_read, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(temp), buffer[0] = '\0', NULL);
		if (read_bytes == 0)
			break ;
		buffer_read[read_bytes] = '\0';
		temp_old = temp;
		temp = ft_strjoin(temp_old, buffer_read);
		free(temp_old);
		if (!temp)
			return (NULL);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	buffers[65536][BUFFER_SIZE + 1];
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 65535)
		return (NULL);
	if (ft_strchr(buffers[fd], '\n'))
		return (line = get_line_buffer(buffers[fd]), buffer_move(buffers[fd]),
			line);
	temp = ft_strdup(buffers[fd]);
	if (!temp)
		return (NULL);
	buffers[fd][0] = '\0';
	temp = read_to_buffer(fd, buffers[fd], temp);
	if (!temp)
		return (NULL);
	line = get_line_buffer(temp);
	if (line && temp[0])
		ft_strlcpy(buffers[fd], temp + ft_strlen(line), BUFFER_SIZE + 1);
	free(temp);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int		fd;
// 	int		fd2;
// 	char	*next_line;
// 	int		i;

// 	i = 0;
// 	fd = open("test.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	while (i++ < 3)
// 	{
// 		next_line = get_next_line(fd);
// 		printf("Line %i file 1: %s", i, next_line);
// 		free(next_line);
// 		next_line = get_next_line(fd2);
// 		printf("Line %i file 2: %s", i, next_line);
// 		free(next_line);
// 	}
// 	close(fd);
// 	return (0);
// }
