/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:48:49 by daong             #+#    #+#             */
/*   Updated: 2024/11/06 01:40:41 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Create a image object. From left to right, create ceiling and floor
 * 
 * @param data 
 * @param img 
 */
static void	create_image(t_data *data, t_img *img)
{
	int	x;
	int	y;

	x = -1;
	while (++x < data->mlx->display_size_x)
	{
		y = -1;
		while (++y < data->mlx->display_size_y / 2)
			ft_mlx_pixel_put(img, x, y, data->texture->ceiling_color);
		while (++y < data->mlx->display_size_y)
			ft_mlx_pixel_put(img, x, y, data->texture->floor_color);
	}
	return ;
}

/**
 * @brief render background with floor and ceiling
 * 
 * @param data 
 */
int	render_background(t_data *data)
{
	t_img img;

	img.img_ptr = mlx_new_image(data->mlx->mlx_ptr, data->mlx->display_size_x,
			data->mlx->display_size_y);
	if (!img.img_ptr)
		return (1);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (!img.addr)
		return (1);
	create_image(data, &img);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, img.img_ptr, 0, 0);
	mlx_destroy_image(data->mlx->mlx_ptr, img.img_ptr);
	return (0);
}
