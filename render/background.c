/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:48:49 by daong             #+#    #+#             */
/*   Updated: 2024/11/27 17:28:32 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief init background and active images
 * When creating background, places pixels in image to create ceiling and floor
 * (From left to right, create ceiling then floor)
 * 
 * @param data 
 */
int	init_display_images(t_data *data)
{
	int		x;
	int		y;

	if (!data->display->background.img_ptr)
	{
		data->display->background = init_blank_image(data,
				data->mlx->display_size_x,
				data->mlx->display_size_y);
		x = -1;
		while (++x < data->mlx->display_size_x)
		{
			y = -1;
			while (++y < data->mlx->display_size_y / 2)
				ft_mlx_pixel_put(data->display->background, x, y,
					data->texture->ceiling_color);
			while (++y < data->mlx->display_size_y)
				ft_mlx_pixel_put(data->display->background, x, y,
					data->texture->floor_color);
		}
	}
	if (!data->display->active.img_ptr)
		data->display->active = init_blank_image(data,
				data->mlx->display_size_x,
				data->mlx->display_size_y);
	return (0);
}
