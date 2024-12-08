/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 09:49:58 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/08 09:51:16 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief create visited map
 *
 * @param data
 */
static void	create_visited_map(t_data *data)
{
	int	i;

	i = 0;
	data->visited_map = (int **)ft_calloc(data->map_size_y + 2, sizeof(int *));
	while (i < data->map_size_y + 2)
	{
		data->visited_map[i] = (int *)ft_calloc(data->map_size_x + 2,
				sizeof(int));
		i++;
	}
}

/**
 * @brief flood fill operation to check for leaks into the wall
 *
 * @param data
 * @param x
 * @param y
 * @return bool true if floodfill hit wall or alr visited/success,
 * false if out of bound/leak found
 */
static bool	flood_fill(t_data *data, char **temp_map, int x, int y)
{
	char	cell;
	bool	up;
	bool	down;
	bool	left;
	bool	right;

	if (x < 0 || x >= data->map_size_x + 2 || y < 0
		|| y >= data->map_size_y + 2)
		return (true);
	cell = temp_map[y][x];
	if (data->visited_map[y][x] == 1 || cell == WALL)
		return (true);
	if (cell == FLOOR || ft_strchr(DIRECTION, cell))
		return (false);
	data->visited_map[y][x] = 1;
	temp_map[y][x] = 'X';
	up = flood_fill(data, temp_map, x, y - 1);
	down = flood_fill(data, temp_map, x, y + 1);
	left = flood_fill(data, temp_map, x - 1, y);
	right = flood_fill(data, temp_map, x + 1, y);
	return (up && down && left && right);
}

/**
 * @brief main function to check if maps is enclosed
 * 
 * @param data
 * @return bool true if the map is enclosed, false otherwise.
 */
bool	is_map_enclosed(t_data *data)
{
	create_visited_map(data);
	if (flood_fill(data, data->temp_map, 0, 0) == false)
	{
		free_temp_map(data);
		free_visited_map(data);
		return (false);
	}
	free_temp_map(data);
	free_visited_map(data);
	return (true);
}
