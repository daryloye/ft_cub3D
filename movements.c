/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:41:25 by daong             #+#    #+#             */
/*   Updated: 2024/11/11 23:33:11 by daong            ###   ########.fr       */
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

	new_x = data->player->x_pos + x;
	new_y = data->player->y_pos + y;
	if (data->map[(int)(new_y)][(int)(new_x)] == '1')
		return ;
	data->player->x_pos = new_x;
	data->player->y_pos = new_y;
	return ;
}

/**
 * @brief update player position and rotation values then render screen. RAD = DEG * PI / 180
 * 
 * @param data 
 */
int	do_movements(t_data *data)
{
	if (data->keys[W])
		check_wall(data, (sin(data->player->rot_deg) / data->player->move_speed),
			-(cos(data->player->rot_deg) / data->player->move_speed));
	if (data->keys[A])
		check_wall(data, -(cos(data->player->rot_deg) / data->player->move_speed),
			-(sin(data->player->rot_deg) / data->player->move_speed));
	if (data->keys[S])
		check_wall(data, -(sin(data->player->rot_deg) / data->player->move_speed),
			(cos(data->player->rot_deg) / data->player->move_speed));
	if (data->keys[D])
		check_wall(data, (cos(data->player->rot_deg) / data->player->move_speed),
			(sin(data->player->rot_deg) / data->player->move_speed));
	if (data->keys[LEFT_ARROW])
		data->player->rot_deg = fmod((data->player->rot_deg
			- data->player->rot_speed + M_PI * 2), M_PI * 2);
	if (data->keys[RIGHT_ARROW])
		data->player->rot_deg = fmod((data->player->rot_deg
			+ data->player->rot_speed), M_PI * 2);
	return (render(data), 1);
}
