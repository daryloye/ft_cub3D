/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:00:29 by daong             #+#    #+#             */
/*   Updated: 2024/11/26 21:52:47 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	copy_texture_to_display(t_data *data)
{
	char	*src;
	char	*dst;
	int		x;
	int		y;
	int x_start = 100;
	int y_start = 100;
	
	if (!data || !data->texture || !data->display) {
		fprintf(stderr, "Error: data, texture, or display is NULL.\n");
		return;
	}
	if (!data->texture->north.addr || !data->display->active.addr) {
		fprintf(stderr, "Error: Texture or display not properly initialized.\n");
		return;
	}
	x = -1;
	while (++x < 100)
	{
		y = -1;
		while (++y < 100)
		{
			src = data->texture->north.addr
				+ y * data->texture->north.line_length
				+ x * data->texture->north.bits_per_pixel / 8;
			dst = data->display->active.addr
				+ (y_start + y) * data->display->active.line_length
				+ (x_start + x) * data->display->active.bits_per_pixel / 8;
			*(unsigned int *)dst = *(unsigned int *)src;
		}
	}
	return ;
}

/**
 * @brief Takes data on the wall height and the wall texture, and renders the wall onto the mlx display
 * 
 * @param data 
 * @param ray 
 * @param height 
 */
static void	render_wall(t_data *data, double *ray, int height)
{
	int	y;
	int	center;

	center = data->mlx->display_size_y / 2;
	y = center - height;
	while (++y < center + height)
	{
		if (ray[RAY_DIR] == NORTH)
			ft_mlx_pixel_put(data->display->active, (int)ray[X_PIX], y, create_trgb(0, 0, 0, 0));
		if (ray[RAY_DIR] == SOUTH)
			ft_mlx_pixel_put(data->display->active, (int)ray[X_PIX], y, create_trgb(0, 100, 0, 0));
		if (ray[RAY_DIR] == EAST)
			ft_mlx_pixel_put(data->display->active, (int)ray[X_PIX], y, create_trgb(0, 0, 100, 0));
		if (ray[RAY_DIR] == WEST)
			ft_mlx_pixel_put(data->display->active, (int)ray[X_PIX], y, create_trgb(0, 0, 0, 100));
	}
	copy_texture_to_display(data);
	return ;
}

/**
 * @brief calculate the height of the wall based on the player distance to the wall.
 * Then renders the wall to the display
 * 
 * @param data 
 * @param ray 
 */
void	calculate_wall_height(t_data *data, double *ray)
{
	double	height;

	height = data->display->max_wall_height_pix
		- (ray[RAY_DIST] - data->display->min_dist_to_wall) * 100;
		//data->display->coord_to_pix_scale;
	render_wall(data, ray, (int)height);
	return ;
}
