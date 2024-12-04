/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:21:05 by daong             #+#    #+#             */
/*   Updated: 2024/12/04 10:51:20 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	disp(t_data *data, int x_start, int y_start, int color)
{
	int		x;
	int		y;
	int		border_color;

	border_color = trgb(0, 0, 0, 0);
	x = -1;
	while (++x < data->minimap->wall_length)
	{
		y = -1;
		while (++y < data->minimap->wall_length)
		{
			if (x == 0 || x == data->minimap->wall_length - 1
				|| y == 0 || y == data->minimap->wall_length - 1)
				ft_mlx_pixel_put(data->minimap->background,
					x + x_start, y + y_start, border_color);
			else
				ft_mlx_pixel_put(data->minimap->background,
					x + x_start, y + y_start, color);
		}
	}
	return ;
}

/**
 * @brief render minimap wall and floor
 * 
 * @param data 
 * @return int 
 */
int	minimap_background(t_data *data)
{
	int	x;
	int	y;
	int	length;

	length = data->minimap->wall_length;
	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '1')
				disp(data, x * length, y * length, trgb(0, 128, 128, 128));
			else if (data->map[y][x] == '0')
				disp(data, x * length, y * length, trgb(0, 255, 255, 255));
			else if (data->map[y][x] == 'o')
				disp(data, x * length, y * length, trgb(0, 128, 128, 255));
			else if (data->map[y][x] == 'O')
				disp(data, x * length, y * length, trgb(0, 0, 0, 128));
		}
	}
	return (0);
}
