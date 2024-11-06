/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:41:25 by daong             #+#    #+#             */
/*   Updated: 2024/11/07 03:32:47 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	wasd(t_data *data)
{
	if (data->keys[W])
	{
		data->player->x += sin(data->player->rot_deg) / data->player->move_speed;
		data->player->y -= cos(data->player->rot_deg) / data->player->move_speed;
	}
	else if (data->keys[A])
	{
		data->player->x -= cos(data->player->rot_deg) / data->player->move_speed;
		data->player->y -= sin(data->player->rot_deg) / data->player->move_speed;
	}
	else if (data->keys[S])
	{
		data->player->x -= sin(data->player->rot_deg) / data->player->move_speed;
		data->player->y += cos(data->player->rot_deg) / data->player->move_speed;
	}
	else if (data->keys[D])
	{
		data->player->x += cos(data->player->rot_deg) / data->player->move_speed;
		data->player->y += sin(data->player->rot_deg) / data->player->move_speed;
	}
	// if (data->player->x) > 
	return ;
}

/**
 * @brief update player position and rotation values then render screen. RAD = DEG * PI / 180
 * 
 * @param data 
 */
int	do_movements(t_data *data)
{
	if (data->keys[W] || data->keys[A] || data->keys[S] || data->keys[D])
		wasd(data);

	if (data->keys[LEFT_ARROW])
		data->player->rot_deg = fmod((data->player->rot_deg
			- data->player->rot_speed + 6.28), 6.28);
	if (data->keys[RIGHT_ARROW])
		data->player->rot_deg = fmod((data->player->rot_deg
			+ data->player->rot_speed), 6.28);
	return (render(data), 1);
}
