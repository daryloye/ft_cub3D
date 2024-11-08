/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <wkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:29:48 by wkoh              #+#    #+#             */
/*   Updated: 2024/11/07 17:29:51 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief flood fill operation
 *
 * @param data
 * @param x
 * @param y
 * @return int 1 if floodfill success, 0 if floodfill fail
 */
static int	floodfill(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	if (x < 0 || x >= data->map_size_x || y < 0 || y >= data->map_size_y || data->map[y][x] == WALL)
		return (0);
	while (i < 4)
	{
		if (data->map[y][x] == DIRECTION[i])
		{
			data->directions_found[i] = 1;
			return (1);
		}
		i++;
	}
	if (data->map[y][x] == FLOOR)
	{
		data->map[y][x] = WALL;
		if (floodfill(data, x - 1, y) == 0 ||
			floodfill(data, x + 1, y) == 0 ||
			floodfill(data, x, y - 1) == 0 ||
			floodfill(data, x, y + 1) == 0)
			return (0);
	}
	return (1);
}

/**
 * @brief check the map if enclosed using flood fill
 * y is row, x is col [x1,x2,x3],[x4,x5,x6] -> y1 is [x1,x2,x3] and y2 is [x4,x5,x6]  
 *
 * @param data
 * @return bool true if the map is enclosed and only 1 direction found, false otherwise.
 */
static bool	check_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_size_y)
	{
		x = 0;
		while (x < data->map_size_x)
		{
			if (data->map[y][x] == FLOOR)
			{
				if (floodfill(data, x, y) == 0)
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

/**
 * @brief check if only 1 direction found 
 * 
 * @param directions_found[4]
 * @return bool true if only single direction found, false otherwise.
 */
static bool	check_single_direction(int directions_found[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (directions_found[i] == 0)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief main function to check if maps is enclosed and only 1 direction found 
 * 
 * @param data
 * @return bool true if the map is enclosed and only 1 direction found, false otherwise.
 */
static bool	is_map_enclosed(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->directions_found[i] = 0;
		i++;
	}
	if (check_map(data) == false)
		return (false);
	if (check_single_direction(data->directions_found) == false)
		return (false);
	return (true);
}

/**
 * @brief get map identifier
 * 
 * @param line
 * @return int return 0 or 1  if successful, -1 on error
 */
static int	map_identifier(char *line)
{
	if (ft_strncmp(line, "1", 1) == 0)
		return (0);
	return (-1);
}

/**
 * @brief get map size and assign to data
 *
 * @param data
 * @return int  0 if success
 */
int	get_map_size(t_data *data, char **text, int i)
{
	int	map_size_x;
	int	map_size_y;
	int	row_len;
	int	j;

	map_size_x = 0;
	map_size_y = 0;
	j = i;
	while (text[i + map_size_y])
		map_size_y++;
	while (j < (i + map_size_y))
	{
		row_len = ft_strlen(text[j]);
		if (row_len > map_size_x)
			map_size_x = row_len;
		j++;
	}
	data->map_size_x = map_size_x;
	data->map_size_y = map_size_y;
	return (0);
}

/**
 * @brief read each map line and assign to map array if valid
 *
 * @param line
 * @param data
 * @param text
 * @param i
 * @return int 0 if success, -1 if fail 
 */
static int	read_map_line(char *line, t_data *data, char **text, int i)
{
	int	identifier;
	int	j;

	identifier = map_identifier(line);
	if (identifier == -1)
		return (0);
	if (identifier == 0)
	{	
		if (!data->map)
		{
			get_map_size(data, text, i);
			data->map = ft_calloc(sizeof(char *), data->map_size_y + 1);
			if (!is_map_enclosed(data))
			{
				ft_printf("Error: Map is not enclosed by '1's\n");
				//free data->map, 
				return (-1);
			}
		}
	}
	j = i;
	while (text[j])
	{
		data->map[j - i] = ft_strdup(text[j]);
		j++;
        }
	return (0);
}

/**
 * @brief Iterate through the provided text array to find map

 * 
 * @param data
 * @param text
 * @return int 
 */
int	get_map(t_data *data, char **text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (read_map_line(text[i], data, text, i) != 0)
			return (ft_printf("Error\nInvalid map: %s\n", text[i]), 1);
		if (data->map[i] != NULL)
			break;
		i++;
	}
	return (0);
}

