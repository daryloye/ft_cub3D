/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:57:11 by daong             #+#    #+#             */
/*   Updated: 2024/11/11 01:02:40 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	minimap_fov(t_data *data)
{
	float	start[2];
	float	end[2];

	start[0] = (data->player->x_pos * data->minimap->wall_length);
	start[1] = (data->player->y_pos * data->minimap->wall_length);
	end[0] = 0;
	end[1] = 0;
	dda(data->minimap->img, start, end, create_trgb(0, 0, 255, 0));
}
