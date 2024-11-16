/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:57:11 by daong             #+#    #+#             */
/*   Updated: 2024/11/16 18:00:11 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double	horN(t_data *data, double ray[POS_COUNT], double ray_angle)
{
	double	new_x;
	double	new_y;

	if (ray_angle >= (M_PI * 0.5) - 0.001 && ray_angle <= (M_PI * 1.5) + 0.001)
		return (0);
	ray[END_Y] = (int)ray[START_Y];
	ray[END_X] = (ray[START_Y] - ray[END_Y]) * tan(ray_angle) + ray[START_X];
	while (1)
	{
		new_x = ray[END_X] + tan(ray_angle);
		new_y = ray[END_Y] - 1;
		if (new_y < 0 || new_y > data->map_size_x
			|| new_x < 0 || new_x > data->map_size_x
			|| data->map[(int)ray[END_Y] - 1][(int)ray[END_X]] == '1')
			break ;
		ray[END_X] = new_x;
		ray[END_Y] = new_y;
	}
	return (sqrt(pow(ray[START_X] - ray[END_X], 2) + pow(ray[START_Y] - ray[END_Y], 2)));
}

static double	horS(t_data *data, double ray[POS_COUNT], double ray_angle)
{
	double	new_x;
	double	new_y;

	if (ray_angle >= (M_PI * 1.5) - 0.001 || ray_angle <= (M_PI * 0.5) + 0.001)
		return (0);
	ray[END_Y] = (int)ray[START_Y] + 1;
	ray[END_X] = (ray[START_Y] - ray[END_Y]) * tan(ray_angle) + ray[START_X];
	while (1)
	{
		new_x = ray[END_X] - tan(ray_angle);
		new_y = ray[END_Y] + 1;
		if (new_y < 0 || new_y > data->map_size_x
			|| new_x < 0 || new_x > data->map_size_x
			|| data->map[(int)ray[END_Y]][(int)ray[END_X]] == '1')
			break ;
		ray[END_X] = new_x;
		ray[END_Y] = new_y;
	}
	return (sqrt(pow(ray[START_X] - ray[END_X], 2) + pow(ray[START_Y] - ray[END_Y], 2)));
}

static double	verE(t_data *data, double ray[POS_COUNT], double ray_angle)
{
	double	new_x;
	double	new_y;

	if (ray_angle >= M_PI - 0.001 && ray_angle <= 0.001)
		return (0);
	ray[END_X] = (int)ray[START_X] + 1;
	ray[END_Y] = ray[START_Y] - (ray[END_X] - ray[START_X]) / tan(ray_angle);
	while (1)
	{
		new_x = ray[END_X] + 1;
		new_y = ray[END_Y] - (ray[END_X] - ray[START_X]) / tan(ray_angle);
		if (new_y < 0 || new_y > data->map_size_x
			|| new_x < 0 || new_x > data->map_size_x
			|| data->map[(int)ray[END_Y]][(int)ray[END_X] - 1] == '1')
			break ;
		ray[END_X] = new_x;
		ray[END_Y] = new_y;
	}
	return (sqrt(pow(ray[START_X] - ray[END_X], 2) + pow(ray[START_Y] - ray[END_Y], 2)));
}

// static double	verW(t_data *data, double ray[POS_COUNT], double ray_angle)
// {
// 	double	new_x;
// 	double	new_y;

// 	if (ray_angle >= -0.001 && ray_angle <= M_PI + 0.001)
// 		return (0);
// 	ray[END_Y] = (int)ray[START_Y] + 1;
// 	ray[END_X] = (ray[START_Y] - ray[END_Y]) * tan(ray_angle) + ray[START_X];
// 	while (1)
// 	{
// 		new_x = ray[END_X] - tan(ray_angle);
// 		new_y = ray[END_Y] + 1;
// 		if (new_y < 0 || new_y > data->map_size_x
// 			|| new_x < 0 || new_x > data->map_size_x
// 			|| data->map[(int)ray[END_Y]][(int)ray[END_X]] == '1')
// 			break ;
// 		ray[END_X] = new_x;
// 		ray[END_Y] = new_y;
// 	}
// 	return (sqrt(pow(ray[START_X] - ray[END_X], 2) + pow(ray[START_Y] - ray[END_Y], 2)));
// }

static void	ray_to_horizontal(t_data *data, double ray_angle, int color)
{
	double	ray_h[POS_COUNT];
	double	ray_v[POS_COUNT];
	double	*ray_r;
	int		i;

	ray_h[START_X] = data->player->x_pos;
	ray_h[START_Y] = data->player->y_pos;
	ray_v[START_X] = data->player->x_pos;
	ray_v[START_Y] = data->player->y_pos;
	if (horN(data, ray_h, ray_angle) + horS(data, ray_h, ray_angle)
		> verE(data, ray_v, ray_angle))
		ray_r = ray_v;
	else
		ray_r = ray_h;
	i = -1;
	while (++i < POS_COUNT)
		ray_r[i] *= data->minimap->wall_length;
	dda(data->minimap->img, ray_r, color);
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

	ray_to_horizontal(data, ray_angle, color);
	return (0);
}
