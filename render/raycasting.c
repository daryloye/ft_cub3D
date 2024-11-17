/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:57:11 by daong             #+#    #+#             */
/*   Updated: 2024/11/17 23:20:38 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	horN(t_data *data, double *ray, double ray_angle)
{
	double	new_x;
	double	new_y;

	ft_memset(ray, 0, POS_COUNT);
	ray[START_X] = data->player->x_pos;
	ray[START_Y] = data->player->y_pos;
	if (ray_angle >= (M_PI * 0.5) - 0.001 && ray_angle <= (M_PI * 1.5) + 0.001)
		return ;
	new_y = (int)ray[START_Y];
	new_x = (ray[START_Y] - new_y) * tan(ray_angle) + ray[START_X];
	if (new_x < 0 || new_x > data->map_size_x)
		return ;
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
	return ;
}

static void	horS(t_data *data, double *ray, double ray_angle)
{
	double	new_x;
	double	new_y;

	ft_memset(ray, 0, POS_COUNT);
	ray[START_X] = data->player->x_pos;
	ray[START_Y] = data->player->y_pos;
	if (ray_angle >= (M_PI * 1.5) - 0.001 || ray_angle <= (M_PI * 0.5) + 0.001)
		return ;
	new_y = (int)ray[START_Y] + 1;
	new_x = (ray[START_Y] - new_y) * tan(ray_angle) + ray[START_X];
	if (new_x < 0 || new_x > data->map_size_x)
		return ;
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
	return ;
}

static void	verE(t_data *data, double *ray, double ray_angle)
{
	double	new_x;
	double	new_y;

	ft_memset(ray, 0, POS_COUNT);
	ray[START_X] = data->player->x_pos;
	ray[START_Y] = data->player->y_pos;
	if (ray_angle >= M_PI - 0.001 || ray_angle <= 0.001)
		return ;
	new_x = (int)ray[START_X] + 1;
	new_y = ray[START_Y] - (new_x - ray[START_X]) / tan(ray_angle);
	if (new_y < 0 || new_y > data->map_size_y)
		return ;
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
	return ;
}

static void	verW(t_data *data, double *ray, double ray_angle)
{
	double	new_x;
	double	new_y;

	ft_memset(ray, 0, POS_COUNT);
	ray[START_X] = data->player->x_pos;
	ray[START_Y] = data->player->y_pos;
	if (ray_angle >= -0.001 && ray_angle <= M_PI + 0.001)
		return ;
	new_x = (int)ray[START_X];
	new_y = ray[START_Y] - (new_x - ray[START_X]) / tan(ray_angle);
	if (new_y < 0 || new_y > data->map_size_y)
		return ;
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
	return ;
}

static double	dist(double ray[POS_COUNT])
{
	double	x_sq;
	double	y_sq;

	if ((int)ray[END_X] == 0 || (int)ray[END_Y] == 0)
		return (0);
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
	double	ray_N[POS_COUNT];
	double	ray_S[POS_COUNT];
	double	ray_E[POS_COUNT];
	double	ray_W[POS_COUNT];

	horN(data, ray_N, ray_angle);
	horS(data, ray_S, ray_angle);
	verE(data, ray_E, ray_angle);
	verW(data, ray_W, ray_angle);

	printf("NORTH: X = %.2f, Y = %.2f, dist = %.2f\n", ray_N[END_X], ray_N[END_Y], dist(ray_N));
	printf("SOUTH: X = %.2f, Y = %.2f, dist = %.2f\n", ray_S[END_X], ray_S[END_Y], dist(ray_S));
	printf("EAST: X = %.2f, Y = %.2f, dist = %.2f\n", ray_E[END_X], ray_E[END_Y], dist(ray_E));
	printf("WEST: X = %.2f, Y = %.2f, dist = %.2f\n", ray_W[END_X], ray_W[END_Y], dist(ray_W));
	printf("\n");
	if (dist(ray_N) + dist(ray_S) <= dist(ray_E) + dist(ray_W))
	{
		if (ray_N[END_X] != 0)
			dda_minimap(data, ray_N, color);
		else if (ray_S[END_X] != 0)
			dda_minimap(data, ray_S, color);
	}
	else if (dist(ray_E) + dist(ray_W) <= dist(ray_N) + dist(ray_S))
	{
		if (ray_E[END_X] != 0)
			dda_minimap(data, ray_E, color);
		else if (ray_W[END_X] != 0)
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
