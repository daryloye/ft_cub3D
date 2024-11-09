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

// Function to print the char** map
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

	printf("Floodfill called at (x = %d, y = %d)\n", x, y);
	i = 0;
	if (x < 0 || x >= data->map_size_x || y < 0 || y >= data->map_size_y
		|| data->map[y][x] == WALL)
	{
		printf("Out of bounds at (x = %d, y = %d)\n", x, y);
		return (0);
	}
	if (data->visited[y][x] == 1)
	{
		printf("Already visited at (x = %d, y = %d)\n", x, y);
		return (1);
	}
	data->visited[y][x] = 1;
	while (i < 4)
	{
		if (data->map[y][x] == DIRECTION[i])
		{
			printf("Found direction '%c' at (x = %d, y = %d)\n", DIRECTION[i], x, y);
			data->directions_found[i] = 1;
			return (1);
		}
		i++;
	}
	if (data->map[y][x] == FLOOR)
	{
		printf("Found FLOOR at (x = %d, y = %d), marking as WALL\n", x, y);
		data->map[y][x] = 'F';
		if (floodfill(data, x - 1, y) == 0 ||
			floodfill(data, x + 1, y) == 0 ||
			floodfill(data, x, y - 1) == 0 ||
			floodfill(data, x, y + 1) == 0)
		{
			printf("Floodfill failed at (x = %d, y = %d)\n", x, y);	
			return (0);
		}
	}
	printf("Floodfill successful at (x = %d, y = %d)\n", x, y);
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
//			printf("Checking position: y = %d, x = %d\n", y, x);
			if (data->map[y] && x < (int)ft_strlen(data->map[y]) && data->map[y][x] != '\0')
			{
				printf("Checking position: y = %d, x = %d, content = '%c'\n", y, x, data->map[y][x]);
				if (data->map[y][x] == FLOOR)
				{
					printf("Found FLOOR at y = %d, x = %d\n", y, x);
					if (floodfill(data, x, y) == 0)
					{
						printf("Floodfill failed at y = %d, x = %d\n", y, x);
						return (false);
					}
				}
			}
			x++;
		}
		if (x == data->map_size_x)
			printf("End of row %d reached, moving to row %d\n", y, y + 1);
		y++;
	}
	printf("Map check completed successfully.\n");
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
	{
		ft_printf("IM HERE 1\n");
		return (false);
	}
	if (check_single_direction(data->directions_found) == false)
	{
		ft_printf("IM HERE 2\n");
		return (false);
	}
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

static void	init_visited_map(t_data *data)
{
	int	y;

	y = 0;
	data->visited = (int **)ft_calloc(data->map_size_y, sizeof(int *));
	while (y < data->map_size_y)
	{
		data->visited[y] = (int *)calloc(data->map_size_x, sizeof(int));
		y++;
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
		if (!data->map)
		{
			get_map_size(data, text, i);
			data->map = ft_calloc(data->map_size_y + 1, sizeof(char *));
			j = i;
			while (text[j])
			{
				data->map[j - i] = ft_strdup(text[j]);
				j++;
        		}
        		print_map(data);
//        		init_visited_map(data);
			create another temp map containing this map with a bother of 'F's surrounding it
//			data->map[j - i] = NULL;
			if (!is_map_enclosed(data))
			{
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

