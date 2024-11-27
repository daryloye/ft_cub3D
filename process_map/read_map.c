/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:29:48 by wkoh              #+#    #+#             */
/*   Updated: 2024/11/27 09:24:49 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
static void print_map(t_data *data)
{
	 int	y;

	y = 0;
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

/*
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
*/

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
		data->visited_map[i] = (int *)ft_calloc(data->map_size_x + 2, sizeof(int));
		i++;
	}
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
static bool	is_map_enclosed(t_data *data)
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

/**
 * @brief get map identifier
 * 
 * @param line
 * @return int return 0 or 1  if successful, -1 on error
 */
static int	map_identifier(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
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
	while (map_size_y > 0 && (text[i + map_size_y - 1] == NULL
		|| text[i + map_size_y - 1][0] == '\0'
		|| text[i + map_size_y - 1][0] == '\n'))
		map_size_y--;
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
 * @brief Assign F to border (if), pad the remaining
 *if the row is shorter than longest row with 'F' (else: it replaces \n wih 'F')
 *
 * @param data
 */
static void	create_temp_map_with_border(t_data *data)
{
	int	i;
	int	j;
	int	row_len;

	i = 0;
	data->temp_map = (char **)ft_calloc(data->map_size_y + 2, sizeof(char *));
	while (i < data->map_size_y + 2)
	{
		data->temp_map[i] = (char *)ft_calloc(data->map_size_x + 2, sizeof(char));
		j = 0;
		while (j < data->map_size_x + 2)
		{
			if (i == 0 || i == data->map_size_y + 1 || j == 0 || j == data->map_size_x + 1)
				data->temp_map[i][j] = 'F';
			else
			{
				row_len = ft_strlen(data->map[i - 1]);
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
 * @brief set player direction in radians
 *
 * @param c
 * @param data
 */
static void	set_player_rotation(char c, t_data *data)
{
	if (c == 'N')
		data->player->rot_deg = 0;
	else if (c == 'E')
		data->player->rot_deg = PI * 0.5;
	else if (c == 'S')
		data->player->rot_deg = PI;
	else if (c == 'W')
		data->player->rot_deg = PI * 1.5;
}

/**
 * @brief set player pos and direction
 *
 * @param c
 * @param j
 * @param i
 * @param data
 */
static void	process_player_position(char c, int j, int i, t_data *data)
{
	data->player->x_pos = j + 0.5;
	data->player->y_pos = i + 0.5;
	set_player_rotation(c, data);
	return ;
}

/**
 * @brief check map line for invalid chars, if player position found, validate it
 * detact multiple players (invalid), if plater position valid, change the char NSEW to 0.
 *
 * @param line
 * @param i
 * @param player_found
 * @param data
 * @return int 0 if valid, -1 if not valid/invalid char encountered/multiple players detected 
 */
static int	check_map_line(char *line, int i, bool *player_found, t_data *data)
{
	int	j;
	char	c;

	j = 0;	
	while (line[j] != '\0')
	{
		c = line[j];
		if (c != WALL && c != FLOOR && c != DOOR && !ft_strchr(DIRECTION, c) && c != ' ' && c != '\n')
			return (-1);
		if (ft_strchr(DIRECTION, c))
		{
			if (*player_found)
				return (-1);
			*player_found = true;
			process_player_position(c, j, i, data);
			line[j] = '0';
		}
		j++;
	}
	return (0);
}

/**
 * @brief handle empty line, trailing empty line is acceptable
 *empty line within map is invalid
 *
 * @param line
 * @param line_index
 * @param map_size_y
 * @return int 0 if valid/trailing empty lines, -1 if not valid 
 */
static int	handle_empty_line(char *line, int line_index, int map_size_y)
{
	if (line == NULL || line[0] == '\0' || line[0] == '\n')
	{
		if (line_index == map_size_y - 1)
			return (0);
		return (-1);
    }
    return (0);
}

static int	is_door_enclosed(t_data *data, int i, int j)
{
	if ((i > 0 && data->map[i-1][j] != '1') || (i < data->map_size_y - 1 && data->map[i+1][j] != '1'))
	{
		if ((j > 0 && data->map[i][j-1] != '1') || ((size_t)j < ft_strlen(data->map[i]) - 1 && data->map[i][j+1] != '1'))
			return (0);
		else
			return (1);
	}
	return (1);
}

static int	check_door(t_data *data, int i)
{
	int	j;

	j = 0;
	while ((size_t)j < ft_strlen(data->map[i]))
	{
		if (data->map[i][j] == 'D')
		{
			if (!is_door_enclosed(data, i, j))
				return (-1);
		}
		j++;
	}
	return (0);
}

/**
 * @brief check if map is valid, to handle empty line, and to handle invalid char,
 *repeated players and to assign player position and direction
 *
 * @param data
 * @return int 0 if valid, -1 if not valid 
 */
static int	check_map(t_data *data)
{
	int	i;
	bool	player_found;

	i = 0;
	player_found = false;
	while (i < data->map_size_y)
	{
		if (handle_empty_line(data->map[i], i, data->map_size_y) != 0)
			return (-1);
		if (check_map_line(data->map[i], i, &player_found, data) != 0)
			return (-1);
		//check if door D is ecnlosed by 1, either top and bottom, or left or right
		if (check_door(data, i) != 0)
			return (-1);
		i++;
	}
	if (!player_found)
		return (-1);
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
			if (check_map(data) != 0)
				return (-1);
			create_temp_map_with_border(data);
			if (!is_map_enclosed(data))
				return (-1);
		}
	}
	return (0);
}

/**
 * @brief Iterate through the provided text array to find map
 * remove /n character for each row in map
 * 
 * @param data
 * @param text
 * @return int 
 */
int	get_map(t_data *data, char **text)
{
	int	i;
	// int	len;

	i = -1;
	while (text[++i])
	{
		if (read_map_line(text[i], data, text, i) != 0)
			return (print_error("Invalid map"), 1);
		if (data->map && data->map[i] != NULL)
			break;
	}
	// i = -1;
	// while (data->map && data->map[++i])
	// {
	// 	len = ft_strlen(data->map[i]);
	// 	if (data->map[i][len - 1] == '\n')
	// 		data->map[i][len - 1] = '\0';
	// }
	// data->map_size_x--;
	return (0);
}

