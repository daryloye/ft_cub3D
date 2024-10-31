/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:41:25 by daong             #+#    #+#             */
/*   Updated: 2024/10/31 16:18:55 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief update player position and rotation values then render screen
 * 
 * @param data 
 */
int	do_movements(t_data *data)
{
	if (data->keys[4])
		data->player->rot_deg = (data->player->rot_deg + 350) % 360;
	if (data->keys[5])
		data->player->rot_deg = (data->player->rot_deg + 10) % 360;
	render(data);
	return (1);
}
