/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:57:11 by daong             #+#    #+#             */
/*   Updated: 2024/11/14 22:42:38 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void ray_north(t_data *data, double *end)
// {
// 	end[0] = (int)data->player->x_pos;
// 	end[1] = (int)data->player->y_pos;
// 	while (data->map[(int)end[1] - 1][(int)end[0]] != '1')
// 		end[1]--;
// 	end[0] *= data->minimap->wall_length;
// 	end[1] *= data->minimap->wall_length;
// 	return ;
// }

void	horizontal_check(t_data *data, double *end)
{
	double	y_nearest;
	double	x_nearest;

	y_nearest = data->player->y_pos - (int)data->player->y_pos;
	x_nearest = y_nearest * tan(data->player->rot_deg);
	end[0] = (data->player->x_pos + x_nearest) * data->minimap->wall_length;
	
	if (data->player->rot_deg < M_PI * 0.5 || data->player->rot_deg > M_PI * 1.5)
		end[1] = (data->player->y_pos - y_nearest) * data->minimap->wall_length;
	else if (data->player->rot_deg > M_PI * 0.5 && data->player->rot_deg < M_PI * 1.5)
		end[1] = (data->player->y_pos + y_nearest) * data->minimap->wall_length;	
}

void	minimap_fov(t_data *data)
{
	double	start[2];
	double	end[2];

	start[0] = (data->player->x_pos * data->minimap->wall_length);
	start[1] = (data->player->y_pos * data->minimap->wall_length);

	// if (data->player->rot_deg == 0)
	// 	ray_north(data, end);
	// else
		horizontal_check(data, end);
	// else
	// {
	// 	end[0] = 0;
	// 	end[1] = 0;
	// }
		dda(data->minimap->img, start, end, create_trgb(0, 0, 255, 0));
}
