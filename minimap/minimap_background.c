/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:21:05 by daong             #+#    #+#             */
/*   Updated: 2024/11/09 16:17:05 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	*create_wall_image(t_data *data)
{
	int		x;
	int		y;
	int		color;
	int		border_color;
	t_img	img;

	color = create_trgb(0, 128, 128, 128);
	border_color = create_trgb(0, 0, 0, 0);
	img = init_blank_image(data, data->minimap->wall_length,
			data->minimap->wall_length);
	x = -1;
	while (++x < data->minimap->wall_length)
	{
		y = -1;
		while (++y < data->minimap->wall_length)
		{
			if (x == 0 || x == data->minimap->wall_length - 1
				|| y == 0 || y == data->minimap->wall_length - 1)
				ft_mlx_pixel_put(&img, x, y, border_color);
			else
				ft_mlx_pixel_put(&img, x, y, color);
		}
	}
	return (img.img_ptr);
}

static void	*create_floor_image(t_data *data)
{
	int		x;
	int		y;
	int		color;
	int		border_color;
	t_img	img;

	color = create_trgb(0, 255, 255, 255);
	border_color = create_trgb(0, 0, 0, 0);
	img = init_blank_image(data, data->minimap->wall_length,
			data->minimap->wall_length);
	x = -1;
	while (++x < data->minimap->wall_length)
	{
		y = -1;
		while (++y < data->minimap->wall_length)
		{
			if (x == 0 || x == data->minimap->wall_length - 1
				|| y == 0 || y == data->minimap->wall_length - 1)
				ft_mlx_pixel_put(&img, x, y, border_color);
			else
				ft_mlx_pixel_put(&img, x, y, color);
		}
	}
	return (img.img_ptr);
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
	if (!data->minimap->minimap_wall_img)
		data->minimap->minimap_wall_img = create_wall_image(data);
	if (!data->minimap->minimap_floor_img)
		data->minimap->minimap_floor_img = create_floor_image(data);
	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr,
					data->minimap->minimap_wall_img, x * length, y * length);
			else if (data->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr,
					data->minimap->minimap_floor_img, x * length, y * length);
		}
	}
	return (0);
}
