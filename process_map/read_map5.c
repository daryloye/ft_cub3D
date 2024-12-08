/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 09:57:20 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/08 09:57:36 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
 * detact multiple players (invalid), if plater position valid,
 * change the char NSEW to 0.
 *
 * @param line
 * @param i
 * @param player_found
 * @param data
 * @return int 0 if valid, -1 if not valid/invalid char
 * encountered/multiple players detected 
 */
int	check_map_line(char *line, int i, bool *player_found, t_data *data)
{
	int		j;
	char	c;

	j = 0;
	while (line[j] != '\0')
	{
		c = line[j];
		if (c != WALL && c != FLOOR && c != DOORO && c != DOORC
			&& !ft_strchr(DIRECTION, c) && c != ' ' && c != '\n')
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
int	handle_empty_line(char *line, int line_index, int map_size_y)
{
	if (line == NULL || line[0] == '\0' || line[0] == '\n')
	{
		if (line_index == map_size_y - 1)
			return (0);
		return (-1);
	}
	return (0);
}
