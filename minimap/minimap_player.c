/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:19:38 by daong             #+#    #+#             */
/*   Updated: 2024/11/10 12:00:56 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	*create_player_image(t_data *data)
{
	int		x;
	int		y;
	int		color;
	t_img	img;

	color = create_trgb(0, 0, 0, 0);
	img = init_blank_image(data, data->minimap->player_length,
			data->minimap->player_length);
	x = -1;
	while (++x < data->minimap->player_length)
	{
		y = -1;
		while (++y < data->minimap->player_length)
			ft_mlx_pixel_put(&img, x, y, color);
	}
	return (img.img_ptr);
}

static void	create_fov(t_data *data)
{
	float	start[2];
	float	end[2];

	start[0] = (data->player->x_pos * data->minimap->wall_length);
	start[1] = (data->player->y_pos * data->minimap->wall_length);
	end[0] = 0;
	end[1] = 0;
	dda(data, start, end, create_trgb(0, 0, 255, 0));
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
	float	x_img;
	float	y_img;

	wall_length = data->minimap->wall_length;
	player_length = data->minimap->player_length;
	x_img = (data->player->x_pos * wall_length) - (player_length / 2);
	y_img = (data->player->y_pos * wall_length) - (player_length / 2);
	if (!data->minimap->minimap_player_img)
		data->minimap->minimap_player_img = create_player_image(data);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->minimap->minimap_player_img, x_img, y_img);
	create_fov(data);
	return (0);
}
