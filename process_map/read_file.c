/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:21:26 by daong             #+#    #+#             */
/*   Updated: 2024/11/02 18:19:36 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief converts text in fd to array
 * 
 * @param fd 
 * @return char** 
 */
static char	**convert_to_array(int fd)
{
	int		lines;
	char	*str;
	char	**text;
	char	**temp;

	lines = 0;
	text = ft_calloc(sizeof(char *), lines + 1);
	if (!text)
		return (NULL);
	str = get_next_line(fd);
	while (str)
	{
		text[lines++] = str;
		temp = ft_realloc(text, lines);
		if (!temp)
		{
			while (lines > 0)
				free(text[--lines]);
			return (free(text), NULL);
		}
		text = temp;
		str = get_next_line(fd);
	}
	return (text);
}

/**
 * @brief check file is .cub
 * 
 * @param path 
 * @return int 
 */
static int	check_file_name(char *path, char *suffix)
{
	int	pos;

	pos = ft_strlen(path) - 4;
	if (pos < 0 || ft_strncmp(path + pos, suffix, ft_strlen(suffix)) != 0)
		return (1);
	return (0);
}

/**
 * @brief open file, check for errors, store infor in data struct
 * 
 * @param path 
 * @param data 
 * @return int 
 */
int	read_file(char *path, t_data *data)
{
	int		i;
	int		fd;
	char	**text;

	if (check_file_name(path, ".cub") != 0)
		return (ft_printf("Error\nNot a .cub file\n"), 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\n%s\n", strerror(errno)), 1);
	text = convert_to_array(fd);
	
	for (int i = 0; text[i]; i++)
	{
		ft_printf("%s", text[i]);
	}
	// get_texture
	// get_color
	// get_map
	if (!data)
		return (1);
	i = 0;
	while (text[i])
		free(text[i++]);
	free(text);
	close(fd);
	return (0);
}
