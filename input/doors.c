/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:03:39 by daong             #+#    #+#             */
/*   Updated: 2024/12/07 09:42:00 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	replace_map_char(t_data *data, char find, char replace)
{
	int	y;
	int	x;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == find)
				data->map[y][x] = replace;
		}
	}
	return ;
}

/**
 * @brief toggle to open/close doors
 * 
 * @param data 
 */
void	handle_doors(t_data *data)
{
	if (data->keys[KEY_DOOR] == -1)
		replace_map_char(data, DOORC, DOORO);
	if (data->keys[KEY_DOOR] == 1)
		replace_map_char(data, DOORO, DOORC);
	data->keys[KEY_DOOR] *= -1;
}
