/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <wkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:01:09 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/08 12:18:41 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief check if map is valid, to handle empty line,
 * and to handle invalid char,
 *repeated players and to assign player position and direction
 *
 * @param data
 * @return int 0 if valid, -1 if not valid 
 */
int	check_map(t_data *data)
{
	int		i;
	bool	player_found;

	i = 0;
	player_found = false;
	while (i < data->map_size_y)
	{
		if (handle_empty_line(data->map[i], i, data->map_size_y) != 0)
			return (-1);
		if (check_map_line(data->map[i], i, &player_found, data) != 0)
			return (-1);
		if (check_door(data, i) != 0)
			return (-1);
		i++;
	}
	if (!player_found)
		return (-1);
	return (0);
}
/*
void	replace_whitespace_with_zero_mod(char **map, int map_size_y)
{
	int	j;
	int	k;
	int	found_first_one;

	j = 0;
	while (j < map_size_y)
	{
		k = 0;
		found_first_one = 0;
		while (map[j][k])
		{
			if (map[j][k] == '1')
				found_first_one = 1;
			if ((map[j][k] == ' ' || map[j][k] == '\t') && found_first_one)
				map[j][k] = '0';
			k++;
		}
		j++;
	}
}
*/
void	replace_whitespace_with_zero_mod(char **map, int map_size_y)
{
	int	j;
	int	k;

	j = 0;
	while (j < map_size_y)
	{
		k = 0;
		while (map[j][k])
		{
			if (map[j][k] == ' ' || map[j][k] == '\t')
				map[j][k] = '0';
			k++;
		}
		j++;
	}
}
