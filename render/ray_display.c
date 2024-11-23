/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:00:29 by daong             #+#    #+#             */
/*   Updated: 2024/11/22 01:49:00 by daong            ###   ########.fr       */
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
	// check ray direction
	
		ft_mlx_pixel_put(data->display->active, (int)ray[X_PIX], y, create_trgb(0, 0, 0, 0));
	return ;
}

void	calculate_wall_height(t_data *data, double *ray)
{
	double	height;

	// height = data->display->max_wall_height_pix
	// 	- (ray[RAY_DIST] - data->display->min_dist_to_wall)
	// 	* data->display->pix_to_coord_scale;
	height = 100;
	render_wall(data, ray, (int)height);
	return ;
}
