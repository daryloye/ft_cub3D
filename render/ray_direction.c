/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:57:11 by daong             #+#    #+#             */
/*   Updated: 2024/11/19 19:44:58 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	horN(t_data *data, double *ray, double ray_angle)
{
	double	new_x;
	double	new_y;
	double	dist;

	if (ray_angle >= (PI * 0.5) - 0.001 && ray_angle <= (PI * 1.5) + 0.001)
		return (0);
	new_y = (int)ray[START_Y];
	new_x = (ray[START_Y] - new_y) * tan(ray_angle) + ray[START_X];
	if (new_x < 0 || new_x > data->map_size_x)
		return (0);
	while (data->map[(int)new_y - 1][(int)new_x] == '0')
	{
		new_x += tan(ray_angle);
		new_y -= 1;
		if (new_x < 0 || new_x > data->map_size_x)
			return (0);
	}
	dist = get_dist(ray[START_X], ray[START_Y], new_x, new_y);
	if (ray[RAY_DIST] >= 0 && dist > ray[RAY_DIST])
		return (0);
	ray[END_X] = new_x;
	ray[END_Y] = new_y;
	ray[RAY_DIR] = NORTH;
	ray[RAY_DIST] = dist;
	return (1);
}

static int	horS(t_data *data, double *ray, double ray_angle)
{
	double	new_x;
	double	new_y;
	double	dist;

	if (ray_angle >= (PI * 1.5) - 0.001 || ray_angle <= (PI * 0.5) + 0.001)
		return (0);
	new_y = (int)ray[START_Y] + 1;
	new_x = (ray[START_Y] - new_y) * tan(ray_angle) + ray[START_X];
	if (new_x < 0 || new_x > data->map_size_x)
		return (0);
	while (data->map[(int)new_y][(int)new_x] == '0')
	{
		new_x -= tan(ray_angle);
		new_y += 1;
		if (new_x < 0 || new_x > data->map_size_x)
			return (0);
	}
	dist = get_dist(ray[START_X], ray[START_Y], new_x, new_y);
	if (ray[RAY_DIST] >= 0 && dist > ray[RAY_DIST])
		return (0);
	ray[END_X] = new_x;
	ray[END_Y] = new_y;
	ray[RAY_DIR] = SOUTH;
	ray[RAY_DIST] = dist;
	return (1);
}

static int	verE(t_data *data, double *ray, double ray_angle)
{
	double	new_x;
	double	new_y;
	double	dist;

	if (ray_angle >= PI - 0.001 || ray_angle <= 0.001)
		return (0);
	new_x = (int)ray[START_X] + 1;
	new_y = ray[START_Y] - (new_x - ray[START_X]) / tan(ray_angle);
	if (new_y < 0 || new_y > data->map_size_y)
		return (0);
	while (data->map[(int)new_y][(int)new_x] == '0')
	{
		new_x += 1;
		new_y -= 1 / tan(ray_angle);
		if (new_y < 0 || new_y > data->map_size_y)
			return (0);
	}
	dist = get_dist(ray[START_X], ray[START_Y], new_x, new_y);
	if (ray[RAY_DIST] >= 0 && dist > ray[RAY_DIST])
		return (0);
	ray[END_X] = new_x;
	ray[END_Y] = new_y;
	ray[RAY_DIR] = EAST;
	ray[RAY_DIST] = dist;
	return (1);
}

static int	verW(t_data *data, double *ray, double ray_angle)
{
	double	new_x;
	double	new_y;
	double	dist;

	if (ray_angle >= -0.001 && ray_angle <= PI + 0.001)
		return (0);
	new_x = (int)ray[START_X];
	new_y = ray[START_Y] - (new_x - ray[START_X]) / tan(ray_angle);
	if (new_y < 0 || new_y > data->map_size_y)
		return (0);
	while (data->map[(int)new_y][(int)new_x - 1] == '0')
	{
		new_x -= 1;
		new_y += 1 / tan(ray_angle);
		if (new_y < 0 || new_y > data->map_size_y)
			return (0);
	}
	dist = get_dist(ray[START_X], ray[START_Y], new_x, new_y);
	if (ray[RAY_DIST] >= 0 && dist > ray[RAY_DIST])
		return (0);
	ray[END_X] = new_x;
	ray[END_Y] = new_y;
	ray[RAY_DIR] = WEST;
	ray[RAY_DIST] = dist;
	return (1);
}

/**
 * @brief Create a single ray by checking for nearest vertical or horizontal border
 * 
 * @param data 
 * @param ray_angle 
 * @param color 
 */
int	create_single_ray(t_data *data, double ray_angle, int color)
{
	double	ray[POS_COUNT];

	ray[START_X] = data->player->x_pos;
	ray[START_Y] = data->player->y_pos;
	ray[END_X] = 0;
	ray[END_Y] = 0;
	ray[RAY_DIST] = -1;

	horN(data, ray, ray_angle);
	horS(data, ray, ray_angle);
	verE(data, ray, ray_angle);
	verW(data, ray, ray_angle);
	if (ray[RAY_DIST] < 0)
		return (ft_printf("Error in raycasting\n"), 1);
	dda_minimap(data, ray, color);

	// if (ray[RAY_DIR] == NORTH)
	// 	ft_printf("NORTH\n");
	// if (ray[RAY_DIR] == SOUTH)
	// 	ft_printf("SOUTH\n");
	// if (ray[RAY_DIR] == EAST)
	// 	ft_printf("EAST\n");
	// if (ray[RAY_DIR] == WEST)
	// 	ft_printf("WEST\n");
	return (0);
}
