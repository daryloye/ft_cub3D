/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:41:25 by daong             #+#    #+#             */
/*   Updated: 2024/11/27 17:37:55 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief check if the new position is in a wall, else update the new position
 * 
 * @param data 
 * @param x 
 * @param y 
 */
static void	check_wall(t_data *data, double x, double y)
{
	double	new_x;
	double	new_y;
	double	min_dist;

	min_dist = data->display->min_dist_to_wall;
	new_x = data->player->x_pos + x;
	new_y = data->player->y_pos + y;
	if (data->map[(int)(new_y - min_dist)][(int)(new_x - min_dist)] == '1'
		|| data->map[(int)(new_y - min_dist)][(int)(new_x + min_dist)] == '1'
		|| data->map[(int)(new_y + min_dist)][(int)(new_x - min_dist)] == '1'
		|| data->map[(int)(new_y + min_dist)][(int)(new_x + min_dist)] == '1')
		return ;
	data->player->x_pos = new_x;
	data->player->y_pos = new_y;
	return ;
}

/**
 * @brief update player position and rotation values then render screen.
 * RAD = DEG * PI / 180
 * 
 * @param data 
 */
int	do_movements(t_data *data)
{
	if (data->keys[W] && data->keys[P] == -1)
		check_wall(data, (sin(data->player->rot_deg)
				* data->player->move_speed),
			-(cos(data->player->rot_deg) * data->player->move_speed));
	if (data->keys[A] && data->keys[P] == -1)
		check_wall(data, -(cos(data->player->rot_deg)
				* data->player->move_speed),
			-(sin(data->player->rot_deg) * data->player->move_speed));
	if (data->keys[S] && data->keys[P] == -1)
		check_wall(data, -(sin(data->player->rot_deg)
				* data->player->move_speed),
			(cos(data->player->rot_deg) * data->player->move_speed));
	if (data->keys[D] && data->keys[P] == -1)
		check_wall(data, (cos(data->player->rot_deg)
				* data->player->move_speed),
			(sin(data->player->rot_deg) * data->player->move_speed));
	if (data->keys[LEFT_ARROW] && data->keys[P] == -1)
		data->player->rot_deg = fmod((data->player->rot_deg
					- data->player->rot_speed + PI * 2), PI * 2);
	if (data->keys[RIGHT_ARROW] && data->keys[P] == -1)
		data->player->rot_deg = fmod((data->player->rot_deg
					+ data->player->rot_speed), PI * 2);
	return (render(data), 1);
}
