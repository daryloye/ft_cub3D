/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:11:59 by daong             #+#    #+#             */
/*   Updated: 2024/06/14 17:22:03 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_buffer(char **buffer_string)
{
	if (*buffer_string)
	{
		free(*buffer_string);
		*buffer_string = NULL;
	}
}

static ssize_t	read_and_store(int fd, char **buffer_string)
{
	char	*dest;
	ssize_t	read_size;
	char	*temp_buffer;

	dest = (char *)malloc(BUFFER_SIZE + 1);
	if (!dest)
	{
		free_buffer (buffer_string);
		return (-1);
	}
	read_size = read(fd, dest, BUFFER_SIZE);
	if (read_size < 0)
	{
		free_buffer (&dest);
		free_buffer (buffer_string);
		return (-1);
	}
	dest[read_size] = '\0';
	temp_buffer = ft_strjoin(*buffer_string, dest);
	free_buffer (&dest);
	free_buffer (buffer_string);
	if (!temp_buffer)
		return (-1);
	*buffer_string = temp_buffer;
	return (read_size);
}

static char	*check_new_line(char **buffer_string)
{
	char	*line_after;
	char	*line;
	char	*temp_buffer;
	int		line_length;

	line_after = ft_strchr(*buffer_string, '\n');
	if (!line_after)
		return (NULL);
	else
	{
		line_length = ft_strlen(*buffer_string) - ft_strlen(line_after + 1);
		line = ft_substr(*buffer_string, 0, line_length);
		if (!line)
			return (NULL);
		temp_buffer = ft_strdup(line_after + 1);
		if (!temp_buffer)
		{
			free_buffer (&line);
			return (NULL);
		}
		free_buffer (buffer_string);
		*buffer_string = temp_buffer;
		return (line);
	}
}

static char	*handle_read_result(ssize_t read_size, char **buffer_string)
{
	char	*line;

	if (read_size == 0)
	{
		if (ft_strlen(*buffer_string) == 0)
		{
			free_buffer(buffer_string);
			return (NULL);
		}
		else
		{
			line = ft_strdup(*buffer_string);
			free_buffer(buffer_string);
			if (!line)
				return (NULL);
			return (line);
		}
	}
	line = check_new_line(buffer_string);
	if (line)
		return (line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer_string;
	char		*line;
	ssize_t		read_size;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (free_buffer(&buffer_string), NULL);
	if (!buffer_string)
		buffer_string = ft_strdup("");
	if (!buffer_string)
		return (NULL);
	line = check_new_line(&buffer_string);
	if (line)
		return (line);
	while (1)
	{
		read_size = read_and_store(fd, &buffer_string);
		if (read_size == -1)
			return (NULL);
		line = handle_read_result(read_size, &buffer_string);
		if (line || !buffer_string)
			return (line);
	}
	return (NULL);
}
