/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:57:11 by daong             #+#    #+#             */
/*   Updated: 2024/11/17 17:59:28 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double	*horN(t_data *data, double ray_angle)
{
	double	new_x;
	double	new_y;
	double	ray[POS_COUNT];

	ray[START_X] = data->player->x_pos;
	ray[START_Y] = data->player->y_pos;
	if (ray_angle >= (M_PI * 0.5) - 0.001 && ray_angle <= (M_PI * 1.5) + 0.001)
		return (NULL);
	new_y = (int)ray[START_Y];
	new_x = (ray[START_Y] - new_y) * tan(ray_angle) + ray[START_X];
	if (new_x < 0 || new_x > data->map_size_x)
		return (NULL);
	ray[END_X] = new_x;
	ray[END_Y] = new_y;
	while (1)
	{
		new_x = ray[END_X] + tan(ray_angle);
		new_y = ray[END_Y] - 1;
		if (new_x < 0 || new_x > data->map_size_x
			|| data->map[(int)ray[END_Y] - 1][(int)ray[END_X]] == '1')
			break ;
		ray[END_X] = new_x;
		ray[END_Y] = new_y;
	}
	return (ray);
}

static double	*horS(t_data *data, double ray_angle)
{
	double	new_x;
	double	new_y;
	double	ray[POS_COUNT];

	ray[START_X] = data->player->x_pos;
	ray[START_Y] = data->player->y_pos;
	if (ray_angle >= (M_PI * 1.5) - 0.001 || ray_angle <= (M_PI * 0.5) + 0.001)
		return (NULL);
	new_y = (int)ray[START_Y] + 1;
	new_x = (ray[START_Y] - new_y) * tan(ray_angle) + ray[START_X];
	if (new_x < 0 || new_x > data->map_size_x)
		return (NULL);
	ray[END_X] = new_x;
	ray[END_Y] = new_y;
	while (1)
	{
		new_x = ray[END_X] - tan(ray_angle);
		new_y = ray[END_Y] + 1;
		if (new_x < 0 || new_x > data->map_size_x
			|| data->map[(int)ray[END_Y]][(int)ray[END_X]] == '1')
			break ;
		ray[END_X] = new_x;
		ray[END_Y] = new_y;
	}
	return (ray);
}

static double	*verE(t_data *data, double ray_angle)
{
	double	new_x;
	double	new_y;
	double	ray[POS_COUNT];

	ray[START_X] = data->player->x_pos;
	ray[START_Y] = data->player->y_pos;
	if (ray_angle >= M_PI - 0.001 || ray_angle <= 0.001)
		return (NULL);
	new_x = (int)ray[START_X] + 1;
	new_y = ray[START_Y] - (new_x - ray[START_X]) / tan(ray_angle);
	if (new_y < 0 || new_y > data->map_size_y)
		return (NULL);
	ray[END_X] = new_x;
	ray[END_Y] = new_y;
	while (1)
	{
		new_x = ray[END_X] + 1;
		new_y = ray[END_Y] - 1 / tan(ray_angle);
		if (new_y < 0 || new_y > data->map_size_y
			|| data->map[(int)ray[END_Y]][(int)ray[END_X]] == '1')
			break ;
		ray[END_X] = new_x;
		ray[END_Y] = new_y;
	}
	return (ray);
}

static double	*verW(t_data *data, double ray_angle)
{
	double	new_x;
	double	new_y;
	double	ray[POS_COUNT];

	ray[START_X] = data->player->x_pos;
	ray[START_Y] = data->player->y_pos;
	if (ray_angle >= -0.001 && ray_angle <= M_PI + 0.001)
		return (NULL);
	new_x = (int)ray[START_X];
	new_y = ray[START_Y] - (new_x - ray[START_X]) / tan(ray_angle);
	if (new_y < 0 || new_y > data->map_size_y)
		return (NULL);
	ray[END_X] = new_x;
	ray[END_Y] = new_y;
	while (1)
	{
		new_x = ray[END_X] - 1;
		new_y = ray[END_Y] + 1 / tan(ray_angle);
		if (new_y < 0 || new_y > data->map_size_y
			|| data->map[(int)ray[END_Y]][(int)ray[END_X] - 1] == '1')
			break ;
		ray[END_X] = new_x;
		ray[END_Y] = new_y;
	}
	return (ray);
}

static double	dist(double ray[POS_COUNT])
{
	double	x_sq;
	double	y_sq;

	x_sq = pow(ray[START_X] - ray[END_X], 2);
	y_sq = pow(ray[START_Y] - ray[END_Y], 2);
	return (sqrt(x_sq + y_sq));
}

/**
 * @brief Create a single ray by checking for nearest vertical or horizontal border
 * 
 * @param data 
 * @param ray_angle 
 * @param color 
 */
static void	create_single_ray(t_data *data, double ray_angle, int color)
{
	double	*ray_N;
	double	*ray_S;
	double	*ray_E;
	double	*ray_W;

	ray_N = horN(data, ray_angle);
	ray_S = horS(data, ray_angle);
	ray_E = verE(data, ray_angle);
	ray_W = verW(data, ray_angle);

	if (dist(ray_N) + dist(ray_S) <= dist(ray_E) + dist(ray_W))
	{
		if (ray_N)
			dda_minimap(data, ray_N, color);
		else if (ray_S)
			dda_minimap(data, ray_S, color);
	}
	else if (dist(ray_E) + dist(ray_W) <= dist(ray_N) + dist(ray_S))
	{
		if (ray_E)
			dda_minimap(data, ray_E, color);
		else if (ray_W)
			dda_minimap(data, ray_W, color);
	}
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

	create_single_ray(data, ray_angle, color);
	return (0);
}
