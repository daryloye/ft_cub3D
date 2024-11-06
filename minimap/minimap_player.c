/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:19:38 by daong             #+#    #+#             */
/*   Updated: 2024/11/07 03:28:43 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	*create_player_image(t_data *data, int player_size)
{
	int		x;
	int		y;
	int		color;
	t_img	img;

	color = create_trgb(0, 0, 0, 0);
	img = init_blank_image(data, player_size, player_size);
	x = -1;
	while (++x < player_size)
	{
		y = -1;
		while (++y < player_size)
			ft_mlx_pixel_put(&img, x, y, color);
	}
	return (img.img_ptr);
}

static void	create_fov(t_data *data, float x_coord, float y_coord)
{
	float	start[2];
	float	end[2];

	start[0] = x_coord;
	start[1] = y_coord;
		
	end[0] = 100;
	end[1] = 100;
	dda(data, start, end, create_trgb(0, 0, 255, 0));
}

/**
 * @brief render player in minimap
 * 
 * @param data 
 * @return int 
 */
int	minimap_player(t_data *data, int wall_length)
{
	int		player_size;
	float	x_coord;
	float	y_coord;

	player_size = 10;
	x_coord = (data->player->x * wall_length) + (wall_length / 2) - (player_size / 2);
	y_coord = (data->player->y * wall_length) + (wall_length / 2) - (player_size / 2);
	if (!data->mlx->minimap_player_img)
		data->mlx->minimap_player_img = create_player_image(data, player_size);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->mlx->minimap_player_img, x_coord, y_coord);
	create_fov(data, x_coord, y_coord);
	return (0);
}
