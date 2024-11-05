/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:32:33 by daong             #+#    #+#             */
/*   Updated: 2024/11/06 01:49:35 by daong            ###   ########.fr       */
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
 * @brief replicates mlx_pixel_put, places a single pixel in (x, y)
 * 
 * @param img 
 * @param x 
 * @param y 
 * @param color 
 */
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return ;
}

/**
 * @brief Cleans data and exits program if anything goes wrong in render
 * 
 * @param data 
 */
static void	render_error(t_data *data)
{
	ft_printf("Error\n%s\n", strerror(errno));
	clean_data(data);
	exit(EXIT_FAILURE);
}

/**
 * @brief Main render function. if error, calls render_error
 * 
 * @param data 
 */
void	render(t_data *data)
{
	if (render_background(data) == 1)
		render_error(data);
	if (render_minimap(data) == 1)
		render_error(data);
	printf("x = %.2f, y = %.2f, rot_deg = %.2f\n", data->player->x, data->player->y, data->player->rot_deg);
	return ;
}
