/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:19:38 by daong             #+#    #+#             */
/*   Updated: 2024/12/04 10:51:20 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	create_player(t_data *data, int x_start, int y_start)
{
	int		x;
	int		y;
	int		color;

	color = trgb(0, 0, 0, 0);
	x = -1;
	while (++x < data->minimap->player_length)
	{
		y = -1;
		while (++y < data->minimap->player_length)
			ft_mlx_pixel_put(data->minimap->active,
				x + x_start, y + y_start, color);
	}
	return ;
}

/**
 * @brief render player in minimap
 * 
 * @param data
 * @return int 
 */
int	minimap_player(t_data *data)
{
	int		wall_length;
	int		player_length;
	double	x_start;
	double	y_start;

	wall_length = data->minimap->wall_length;
	player_length = data->minimap->player_length;
	x_start = (data->player->x_pos * wall_length) - (player_length / 2);
	y_start = (data->player->y_pos * wall_length) - (player_length / 2);
	create_player(data, x_start, y_start);
	return (0);
}
