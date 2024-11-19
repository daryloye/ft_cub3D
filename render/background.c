/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:48:49 by daong             #+#    #+#             */
/*   Updated: 2024/11/19 20:50:12 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Create a image object.
 * Then places pixels in image to create ceiling and floor
 * (From left to right, create ceiling then floor)
 * 
 * @param data 
 */
int	render_background(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < data->mlx->display_size_x)
	{
		y = -1;
		while (++y < data->mlx->display_size_y / 2)
			ft_mlx_pixel_put(data->display->img, x, y,
			data->texture->ceiling_color);
		while (++y < data->mlx->display_size_y)
			ft_mlx_pixel_put(data->display->img, x, y,
			data->texture->floor_color);
	}
	return (0);
}
