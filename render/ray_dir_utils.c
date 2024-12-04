/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dir_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:02:40 by daong             #+#    #+#             */
/*   Updated: 2024/12/04 11:43:53 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief checks that ray is within map boundary
 * 
 * @param data 
 * @param ray 
 * @return int 
 */
int	check_in_map(t_data *data, double *ray)
{
	if (ray[NEW_Y] < 0 || ray[NEW_Y] >= data->map_size_y
		|| ray[NEW_X] < 0
		|| ray[NEW_X] >= ft_strlen(data->map[(int)ray[NEW_Y]]))
		return (1);
	else
		return (0);
}

/**
 * @brief finds dist from player to wall.
 * if current dist is smaller than prev, then update ray with current vars.
 * 
 * @param ray 
 * @return int 
 */
int	check_dist(double *ray, int dir, char map_c)
{
	double	dist;

	dist = get_dist(ray[START_X], ray[START_Y], ray[NEW_X], ray[NEW_Y]);
	if (ray[RAY_DIST] > 0 && dist > ray[RAY_DIST])
		return (1);
	ray[END_X] = ray[NEW_X];
	ray[END_Y] = ray[NEW_Y];
	ray[RAY_DIST] = dist;
	if (map_c == WALL)
		ray[RAY_DIR] = dir;
	else if (map_c == DOORC && (dir == NORTH || dir == SOUTH))
		ray[RAY_DIR] = DOOR_NS;
	else if (map_c == DOORC && (dir == EAST || dir == WEST))
		ray[RAY_DIR] = DOOR_EW;
	return (0);
}
