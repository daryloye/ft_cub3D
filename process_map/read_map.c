/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:29:48 by wkoh              #+#    #+#             */
/*   Updated: 2024/11/11 03:52:27 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
static void print_map(t_data *data)
{
    int y = 0;

    if (!data->map)
    {
        printf("Map is not initialized.\n");
        return;
    }
    printf("PRINITNG MAP\n");
    // Iterate over each row in the map
    while (y < data->map_size_y)
    {
        printf("%s\n", data->map[y]);
        y++;
    }
}
*/
static void	create_visited_map(t_data *data)
{
	int	i;

	i = 0;
	data->visited_map = (int **)ft_calloc(data->map_size_y + 2, sizeof(int *));
	while (i < data->map_size_y + 2)
	{
		data->visited_map[i] = (int *)ft_calloc(data->map_size_x + 2, sizeof(int));
		i++;
	}
}

static void	print_temp_map(char **temp_map, int map_size_x, int map_size_y)
{
	int	y;
	int	x;

	y = 0;
	printf("Temporary Map with Border:\n");
	while (y < map_size_y + 2)
	{
		x = 0;
		while (x < map_size_x + 2)
		{
			printf("%c", temp_map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}


/**
 * @brief flood fill operation to check for leaks into the wall
 *
 * @param data
 * @param x
 * @param y
 * @return bool true if floodfill hit wall or alr visited/success, false if out of bound/leak found
 */

static bool	flood_fill(t_data *data, char **temp_map, int x, int y)
{
	char	cell;
	bool	up;
	bool	down;
	bool	left;
	bool	right;

	if (x < 0 || x >= data->map_size_x + 2 || y < 0 || y >= data->map_size_y + 2)
	{
		printf("Out of bounds: (x=%d, y=%d)\n", x, y);
		return (true);
	}
    cell = temp_map[y][x];
	printf("Checking cell at (x=%d, y=%d): '%c'\n", x, y, cell);
    if (data->visited_map[y][x] == 1 || cell == WALL)
	{
		printf("Cell is a wall at (x=%d, y=%d)\n", x, y);
		return (true);
	}
	if (cell == FLOOR || ft_strchr(DIRECTION, cell))
	{
		printf("Cell is floor or direction at (x=%d, y=%d)\n", x, y);
        return (false);
	}
	data->visited_map[y][x] = 1;
    temp_map[y][x] = 'X';
	printf("Filling cell at (x=%d, y=%d)\n", x, y);
    up = flood_fill(data, temp_map, x, y - 1);
    down = flood_fill(data, temp_map, x, y + 1);
    left = flood_fill(data, temp_map, x - 1, y);
    right = flood_fill(data, temp_map, x + 1, y);
    return (up && down && left && right);
}


/**
 * @brief check if only 1 direction found 
 * 
 * @param directions_found[4]
 * @return bool true if only single direction found, false otherwise.
 */

/**
 * @brief main function to check if maps is enclosed
 * 
 * @param data
 * @return bool true if the map is enclosed, false otherwise.
 */
static bool	is_map_enclosed(t_data *data)
{
	create_visited_map(data);
	if (flood_fill(data, data->temp_map, 0, 0) == false)
	{
		print_temp_map(data->temp_map, data->map_size_x, data->map_size_y);
		ft_printf("Error: Map is not enclosed by walls!\n");
		free_temp_map(data);
		free_visited_map(data);
		return (false);
	}
	free_temp_map(data);
	free_visited_map(data);
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
static int	get_map_size(t_data *data, char **text, int i)
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
	ft_printf("map size x: %d\n", data->map_size_x);
	ft_printf("map size y: %d\n", data->map_size_y);
	return (0);
}

static void create_temp_map_with_border(t_data *data)
{
    int i;
    int j;
    int row_len;

    i = 0;
    data->temp_map = (char **)ft_calloc(data->map_size_y + 2, sizeof(char *));
    while (i < data->map_size_y + 2)
    {
        data->temp_map[i] = (char *)ft_calloc(data->map_size_x + 2, sizeof(char));
        j = 0;
        while (j < data->map_size_x + 2)
        {
            // Fill the border with 'F'
            if (i == 0 || i == data->map_size_y + 1 || j == 0 || j == data->map_size_x + 1)
                data->temp_map[i][j] = 'F';
            else
            {
                row_len = ft_strlen(data->map[i - 1]);
                // Check if the character at (i-1, j-1) is not a newline and within bounds
                if (j - 1 < row_len && data->map[i - 1][j - 1] != '\n')
                    data->temp_map[i][j] = data->map[i - 1][j - 1];
                else
                    data->temp_map[i][j] = 'F';
            }
            j++;
        }
        i++;
    }
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
		if (data->map)
			free_map(data);
		if (!data->map)
		{
			get_map_size(data, text, i);
			data->map = ft_calloc(data->map_size_y + 1, sizeof(char *));
			j = i;
			while (j - i < data->map_size_y)
			{
				data->map[j - i] = ft_strdup(text[j]);
				j++;
			}
			data->map[data->map_size_y] = NULL;
//			print_map(data);
//        	init_visited_map(data);
			create_temp_map_with_border(data);
			print_temp_map(data->temp_map, data->map_size_x, data->map_size_y);
			if (!is_map_enclosed(data))
			{
//				print_visited_map(data);
				ft_printf("Error: Map is not enclosed by '1's\n");
				//free data->map, 
				return (-1);
			}
		}
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
		if (data->map && data->map[i] != NULL)
			break;
		i++;
	}
	return (0);
}

