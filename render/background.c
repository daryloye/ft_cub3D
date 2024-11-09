/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:48:49 by daong             #+#    #+#             */
/*   Updated: 2024/11/09 15:43:34 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Create a image object.
 * Then places pixels in image to create ceiling and floor
 * (From left to right, create ceiling then floor)
 * 
 * @param data 
 * @return void* 
 */
static void	*create_background_image(t_data *data)
{
	int		x;
	int		y;
	t_img	img;

	img = init_blank_image(data, data->mlx->display_size_x,
			data->mlx->display_size_y);
	x = -1;
	while (++x < data->mlx->display_size_x)
	{
		y = -1;
		while (++y < data->mlx->display_size_y / 2)
			ft_mlx_pixel_put(&img, x, y, data->texture->ceiling_color);
		while (++y < data->mlx->display_size_y)
			ft_mlx_pixel_put(&img, x, y, data->texture->floor_color);
	}
	return (img.img_ptr);
}

/**
 * @brief render background with floor and ceiling
 * 
 * @param data 
 */
int	render_background(t_data *data)
{
	if (!data->display->background_img)
	{
		data->display->background_img = create_background_image(data);
		if (!data->display->background_img)
			return (1);
	}
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->display->background_img, 0, 0);
	return (0);
}
