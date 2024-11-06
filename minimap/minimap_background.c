/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:21:05 by daong             #+#    #+#             */
/*   Updated: 2024/11/07 03:18:29 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	*create_wall_image(t_data *data, int length)
{
	int		x;
	int		y;
	int		color;
	int		border_color;
	t_img	img;

	color = create_trgb(0, 128, 128, 128);
	border_color = create_trgb(0, 0, 0, 0);
	img = init_blank_image(data, length, length);
	x = -1;
	while (++x < length)
	{
		y = -1;
		while (++y < length)
		{
			if (x == 0 || x == length - 1 || y == 0 || y == length - 1)
				ft_mlx_pixel_put(&img, x, y, border_color);
			else
				ft_mlx_pixel_put(&img, x, y, color);
		}
	}
	return (img.img_ptr);
}

static void	*create_floor_image(t_data *data, int length)
{
	int		x;
	int		y;
	int		color;
	int		border_color;
	t_img	img;

	color = create_trgb(0, 255, 255, 255);
	border_color = create_trgb(0, 0, 0, 0);
	img = init_blank_image(data, length, length);
	x = -1;
	while (++x < length)
	{
		y = -1;
		while (++y < length)
		{
			if (x == 0 || x == length - 1 || y == 0 || y == length - 1)
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
int	minimap_background(t_data *data, int length)
{
	int	x;
	int	y;

	if (!data->mlx->minimap_wall_img)
		data->mlx->minimap_wall_img = create_wall_image(data, length);
	if (!data->mlx->minimap_floor_img)
		data->mlx->minimap_floor_img = create_floor_image(data, length);
	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr,
					data->mlx->minimap_wall_img, x * length, y * length);
			else if (data->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr,
					data->mlx->minimap_floor_img, x * length, y * length);
		}
	}
	return (0);
}
