/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:53:09 by daong             #+#    #+#             */
/*   Updated: 2024/11/19 20:45:01 by daong            ###   ########.fr       */
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
int	create_trgb(int t, int r, int g, int b)
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
		ft_printf("Failed to create image\n");
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
 * @brief draws line from pos[start] to pos[end]
 * 
 * @param img 
 * @param pos 
 * @param color 
 */
void	dda(t_img img, double pos[POS_COUNT], int color)
{
	double	Xinc;
	double	Yinc;
	int		steps;
	int		i;

	if (abs((int)(pos[END_X] - pos[START_X])) > abs((int)(pos[END_Y] - pos[START_Y])))
		steps = abs((int)(pos[END_X] - pos[START_X]));
	else
		steps = abs((int)(pos[END_Y] - pos[START_Y]));
    Xinc = (pos[END_X] - pos[START_X]) / (double)steps; 
    Yinc = (pos[END_Y] - pos[START_Y]) / (double)steps; 
	i = -1;
    while (++i < steps)
	{ 
        ft_mlx_pixel_put(img, round(pos[START_X]), round(pos[START_Y]), color);
        pos[START_X] += Xinc;
		pos[START_Y] += Yinc;
	}
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

	x_sq = pow(x1 - x2, 2);
	y_sq = pow(y1 - y2, 2);
	return (sqrt(x_sq + y_sq));
}
