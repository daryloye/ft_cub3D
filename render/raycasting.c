/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:57:11 by daong             #+#    #+#             */
/*   Updated: 2024/11/14 18:25:40 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_NE(t_data *data, double ray_angle, double *start, int color)
{
	double	end[2];
	double	corner_angle;
	double	x;
	double	y;

	x = start[0];
	y = start[1];
	corner_angle = atan((float)((int)x + 1) - x / y - (float)((int)y));
	if (ray_angle <= corner_angle)	// check N
	{
		end[0] = x;
		end[1] = (int)y;
	}
	if (ray_angle >= corner_angle)		// check E
	{
		end[0] = (int)x + 1;
		end[1] = y;
	}
	dda(data->minimap->img, start, end, color);
	draw_ray(data, ray_angle, end, color);
}

/**
 * @brief draws ray recursively within a box from start[2] to side of box
 * 
 * @param data 
 * @param ray_angle 
 * @param start 
 */
void	draw_ray(t_data *data, double ray_angle, double *start, int color)
{
	if (ray_angle >= 0 && ray_angle < M_PI * 0.5)	// check wall N and E	--> find end point
		check_NE(data, ray_angle, start, color);
	return ;
}

// /**
//  * @brief initialise angles to corners
//  * 0 = NE, 1 = SE, 2 = SW, 3 = NW
//  * 
//  * @param data 
//  */
// static void	init_corner_angles(t_data *data)
// {
// 	float	x;
// 	float	y;

// 	x = data->player->x_pos;
// 	y = data->player->y_pos;
// 	data->player->corner_angle[0] = atan((float)((int)x + 1) - x / y - (float)((int)y));
// 	data->player->corner_angle[1] = atan((float)((int)y + 1) - y / (float)((int)x + 1) - x) + (M_PI * 0.5);
// 	data->player->corner_angle[2] = atan(x - (float)((int)x) / (float)((int)y + 1) - y) + M_PI;
// 	data->player->corner_angle[3] = atan(y - (float)((int)y) / x - (float)((int)x)) + (M_PI * 1.5);
// 	return ;
// }

/**
 * @brief init fov data for player position and angles to walls
 * 
 * @param data 
 */
int	render_fov(t_data *data)
{
	double	start[2];
	double	ray_angle;
	int		color;

	color = create_trgb(0, 0, 255, 0);
	// init_corner_angles(data);
	start[0] = (data->player->x_pos * data->minimap->wall_length);
	start[1] = (data->player->y_pos * data->minimap->wall_length);

	ray_angle = data->player->rot_deg;				// need to repeat this for multiple rays in fov

	draw_ray(data, ray_angle, start, color);
	return (0);
}
