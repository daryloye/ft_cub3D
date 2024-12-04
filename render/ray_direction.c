/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:57:11 by daong             #+#    #+#             */
/*   Updated: 2024/12/04 11:43:14 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	hor_n(t_data *data, double *ray)
{
	char	map_c;

	if (ray[ANGLE] >= (PI * 0.5) - 0.001 && ray[ANGLE] <= (PI * 1.5) + 0.001)
		return (1);
	ray[NEW_Y] = (int)ray[START_Y];
	ray[NEW_X] = (ray[START_Y] - ray[NEW_Y]) * tan(ray[ANGLE]) + ray[START_X];
	if (check_in_map(data, ray) == 1)
		return (1);
	map_c = data->map[(int)ray[NEW_Y] - 1][(int)ray[NEW_X]];
	while (map_c == FLOOR || map_c == DOORO)
	{
		ray[NEW_X] += tan(ray[ANGLE]);
		ray[NEW_Y] -= 1;
		if (check_in_map(data, ray) == 1)
			return (1);
		map_c = data->map[(int)ray[NEW_Y] - 1][(int)ray[NEW_X]];
	}
	return (check_dist(ray, NORTH, map_c));
}

static int	hor_s(t_data *data, double *ray)
{
	char	map_c;

	if (ray[ANGLE] >= (PI * 1.5) - 0.001 || ray[ANGLE] <= (PI * 0.5) + 0.001)
		return (1);
	ray[NEW_Y] = (int)ray[START_Y] + 1;
	ray[NEW_X] = (ray[START_Y] - ray[NEW_Y]) * tan(ray[ANGLE]) + ray[START_X];
	if (check_in_map(data, ray) == 1)
		return (1);
	map_c = data->map[(int)ray[NEW_Y]][(int)ray[NEW_X]];
	while (map_c == FLOOR || map_c == DOORO)
	{
		ray[NEW_X] -= tan(ray[ANGLE]);
		ray[NEW_Y] += 1;
		if (check_in_map(data, ray) == 1)
			return (1);
		map_c = data->map[(int)ray[NEW_Y]][(int)ray[NEW_X]];
	}
	return (check_dist(ray, SOUTH, map_c));
}

static int	ver_e(t_data *data, double *ray)
{
	char	map_c;

	if (ray[ANGLE] >= PI - 0.001 || ray[ANGLE] <= 0.001)
		return (1);
	ray[NEW_X] = (int)ray[START_X] + 1;
	ray[NEW_Y] = ray[START_Y] - (ray[NEW_X] - ray[START_X]) / tan(ray[ANGLE]);
	if (check_in_map(data, ray) == 1)
		return (1);
	map_c = data->map[(int)ray[NEW_Y]][(int)ray[NEW_X]];
	while (map_c == FLOOR || map_c == DOORO)
	{
		ray[NEW_X] += 1;
		ray[NEW_Y] -= 1 / tan(ray[ANGLE]);
		if (check_in_map(data, ray) == 1)
			return (1);
		map_c = data->map[(int)ray[NEW_Y]][(int)ray[NEW_X]];
	}
	return (check_dist(ray, EAST, map_c));
}

static int	ver_w(t_data *data, double *ray)
{
	char	map_c;

	if (ray[ANGLE] >= -0.001 && ray[ANGLE] <= PI + 0.001)
		return (1);
	ray[NEW_X] = (int)ray[START_X];
	ray[NEW_Y] = ray[START_Y] - (ray[NEW_X] - ray[START_X]) / tan(ray[ANGLE]);
	if (check_in_map(data, ray) == 1)
		return (1);
	map_c = data->map[(int)ray[NEW_Y]][(int)ray[NEW_X] - 1];
	while (map_c == FLOOR || map_c == DOORO)
	{
		ray[NEW_X] -= 1;
		ray[NEW_Y] += 1 / tan(ray[ANGLE]);
		if (check_in_map(data, ray) == 1)
			return (1);
		map_c = data->map[(int)ray[NEW_Y]][(int)ray[NEW_X] - 1];
	}
	return (check_dist(ray, WEST, map_c));
}

/**
 * @brief Create a single ray by checking for nearest vertical or
 * horizontal border. Then sends data to draw wall and minimap
 * 
 * @param data 
 * @param ray_angle 
 * @param color 
 */
int	create_single_ray(t_data *data, double ray_angle, int x_pix)
{
	double	ray[POS_COUNT];

	ft_memset(ray, 0, sizeof(ray));
	ray[X_PIX] = x_pix;
	ray[START_X] = data->player->x_pos;
	ray[START_Y] = data->player->y_pos;
	ray[ANGLE] = ray_angle;
	hor_n(data, ray);
	hor_s(data, ray);
	ver_e(data, ray);
	ver_w(data, ray);
	if (ray[RAY_DIST] <= 0)
		return (print_error("Invalid raycasting distance"), 1);
	dda_minimap(data, ray);
	render_wall(data, ray);
	return (0);
}
