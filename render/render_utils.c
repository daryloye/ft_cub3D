/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:53:09 by daong             #+#    #+#             */
/*   Updated: 2024/12/04 10:51:20 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Create a trgb object
 * 
 * @param t 
 * @param r 
 * @param g 
 * @param b 
 * @return int 
 */
int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * @brief Create a blank image object
 * 
 * @param data 
 * @return t_img 
 */
t_img	init_blank_image(t_data *data, int x, int y)
{
	t_img	img;

	img.img_ptr = NULL;
	img.img_ptr = mlx_new_image(data->mlx->mlx_ptr, x, y);
	if (!img.img_ptr)
		print_error("Failed to create image");
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}

/**
 * @brief replicates mlx_pixel_put, places a single pixel in (x, y)
 * 
 * @param img 
 * @param x 
 * @param y 
 * @param color 
 */
void	ft_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return ;
}

/**
 * @brief returns distance between 2 points
 * 
 * @param ray 
 * @return double 
 */
double	get_dist(double x1, double y1, double x2, double y2)
{
	double	x_sq;
	double	y_sq;

	x_sq = (x1 - x2) * (x1 - x2);
	y_sq = (y1 - y2) * (y1 - y2);
	return (sqrt(x_sq + y_sq));
}
