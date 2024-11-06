/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:41:25 by daong             #+#    #+#             */
/*   Updated: 2024/11/06 11:32:26 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief update player position and rotation values then render screen. RAD = DEG * PI / 180
 * 
 * @param data 
 */
int	do_movements(t_data *data)
{
	if (data->keys[W])
	{
		data->player->x += sin(data->player->rot_deg);
		data->player->y -= cos(data->player->rot_deg);
	}
	if (data->keys[A])
	{
		data->player->x -= cos(data->player->rot_deg);
		data->player->y -= sin(data->player->rot_deg);
	}
	if (data->keys[S])
	{
		data->player->x -= sin(data->player->rot_deg);
		data->player->y += cos(data->player->rot_deg);
	}
	if (data->keys[D])
	{
		data->player->x += cos(data->player->rot_deg);
		data->player->y += sin(data->player->rot_deg);
	}
	if (data->keys[LEFT_ARROW])
		data->player->rot_deg = fmod((data->player->rot_deg
			- 0.1 + 6.28), 6.28);
	if (data->keys[RIGHT_ARROW])
		data->player->rot_deg = fmod((data->player->rot_deg
			+ 0.1), 6.28);
	return (render(data), 1);
}
