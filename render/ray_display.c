/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:00:29 by daong             #+#    #+#             */
/*   Updated: 2024/11/23 14:06:50 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	render_wall(t_data *data, double *ray, int height)
{
	int	y;
	int	center;

	printf("height = %d\n", height);
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
	return ;
}

void	calculate_wall_height(t_data *data, double *ray)
{
	double	height;

	height = data->display->max_wall_height_pix
		- (ray[RAY_DIST] - data->display->min_dist_to_wall) * 100;
		//data->display->coord_to_pix_scale;
	render_wall(data, ray, (int)height);
	return ;
}
