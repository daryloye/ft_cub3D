/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:21:26 by daong             #+#    #+#             */
/*   Updated: 2024/11/10 15:21:06 by wkoh             ###   ########.fr       */
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
 * @param suffix 
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
 * @brief Function to free an array of strings
 * 
 * @param array
 */
static void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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
	i = 0;
	while (text[i])
	{
		ft_printf("%s\n", text[i]);
		i++;
	}
	if (check_identifiers(text) != 0)
	{
		free_array(text);
		close(fd);
		return (1);
	}
	if (get_textures(data, text) != 0)
	{
		free_array(text);
		close(fd);
		return (1);
	}
	if (get_color(data, text) != 0)
	{
		free_array(text);
		close(fd);
		return (1);
	}
//	if (get_map(data, text) != 0)
//	{
//		free_array(text);
//		close(fd);
//		return (1);
//	}
	if (!data)
		return (1);
	free_array(text);
	close(fd);
	return (0);
}
