/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:48:49 by daong             #+#    #+#             */
/*   Updated: 2024/11/02 18:57:00 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	create_ceiling(t_data *data, char *img_addr,
	int size_line, int bits_per_pixel)
{
	char	*pixel;
	int		y;
	int		x;

	y = -1;
	while (++y < data->mlx->horizon_height)
	{
		x = -1;
		while (++x < data->mlx->display_size_x)
		{
			pixel = img_addr + (y * size_line + x * (bits_per_pixel / 8));
			*(unsigned int *)pixel = data->texture->ceiling_color;
		}
	}
	return ;
}

static void	create_floor(t_data *data, char *img_addr,
	int size_line, int bits_per_pixel)
{
	char	*pixel;
	int		y;
	int		x;

	y = data->mlx->horizon_height;
	while (++y < data->mlx->display_size_y)
	{
		x = -1;
		while (++x < data->mlx->display_size_x)
		{
			pixel = img_addr + (y * size_line + x * (bits_per_pixel / 8));
			*(unsigned int *)pixel = data->texture->floor_color;
		}
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
	void	*img_ptr;
	char	*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img_ptr = mlx_new_image(data->mlx->mlx_ptr, data->mlx->display_size_x,
			data->mlx->display_size_y);
	if (!img_ptr)
		return (1);
	img_addr = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	if (!img_addr)
		return (1);
	create_ceiling(data, img_addr, size_line, bits_per_pixel);
	create_floor(data, img_addr, size_line, bits_per_pixel);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, img_ptr, 0, 0);
	mlx_destroy_image(data->mlx->mlx_ptr, img_ptr);
	return (0);
}
