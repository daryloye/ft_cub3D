/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:57:11 by daong             #+#    #+#             */
/*   Updated: 2024/11/15 01:27:20 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_horizontal_intercept(t_data *data, double ray_angle, int color)
{
	double	ray[2];
	double	offset[2];
	double	player[2];

	player[0] = data->player->x_pos;
	player[1] = data->player->y_pos;
	if (ray_angle > (M_PI * 1.5) || ray_angle < (M_PI * 0.5))		// looking up
	{
		ray[1] = (int)player[1];
		ray[0] = (player[1] - ray[1]) * tan(ray_angle) + player[0];
		offset[1] = -1;
		offset[0] = tan(ray_angle);
	}
	if (ray_angle > (M_PI * 0.5) && ray_angle < (M_PI * 1.5))		// looking down
	{
		ray[1] = (int)player[1] + 1;
		ray[0] = (ray[1] - player[1]) * -tan(ray_angle) + player[0];
		offset[1] = 1;
		offset[0] = -tan(ray_angle);
	}
	while (ray[0] >= 0 && ray[0] <= data->map_size_x
			&& ray[1] >= 0 && ray[1] <= data->map_size_y
			&& data->map[(int)(ray[1])][(int)(ray[0])] != '1')
	{
		ray[0] += offset[0];
		ray[1] += offset[1];
	}
	player[0] *= data->minimap->wall_length;
	player[1] *= data->minimap->wall_length;
	ray[0] *= data->minimap->wall_length;
	ray[1] *= data->minimap->wall_length;
	dda(data->minimap->img, player, ray, color);
	return ;
}

/**
 * @brief init fov data for player position and angles to walls
 * 
 * @param data 
 */
int	render_fov(t_data *data)
{
	double	ray_angle;
	int		color;

	color = create_trgb(0, 0, 255, 0);

	ray_angle = data->player->rot_deg;

	get_horizontal_intercept(data, ray_angle, color);
	return (0);
}
