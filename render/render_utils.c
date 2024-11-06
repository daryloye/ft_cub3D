/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:53:09 by daong             #+#    #+#             */
/*   Updated: 2024/11/06 16:31:42 by daong            ###   ########.fr       */
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
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return ;
}

void	dda(t_data *data, float start[2], float end[2], int color)
{
	float	Xinc;
	float	Yinc;
	int		steps;
	int		i;
  
	if (abs((int)(end[0] - start[0])) > abs((int)(end[1] - start[1])))
		steps = abs((int)(end[0] - start[0]));
	else
		steps = abs((int)(end[1] - start[1]));
    Xinc = (end[0] - start[0]) / (float)steps; 
    Yinc = (end[1] - start[1]) / (float)steps; 
	i = -1;
    while (++i < steps)
	{ 
        mlx_pixel_put(data->mlx->mlx_ptr, data->mlx->win_ptr, round(start[0]), round(start[1]), color);
        start[0] += Xinc;
		start[1] += Yinc;
	}
	return ;
}
