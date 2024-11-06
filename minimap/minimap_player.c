/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:19:38 by daong             #+#    #+#             */
/*   Updated: 2024/11/06 23:47:17 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	*create_player_image(t_data *data, int length)
{
	int		x;
	int		y;
	t_img	img;

	img = init_blank_image(data, length, length);
	x = -1;
	while (++x < length)
	{
		y = -1;
		while (++y < length)
			ft_mlx_pixel_put(&img, x, y, create_trgb(0, 0, 0, 0));
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
int	minimap_player(t_data *data)
{
	int		length;
	float	x_coord;
	float	y_coord;

	x_coord = data->mlx->display_size_x / 2 + data->player->x;
	y_coord = data->mlx->display_size_y / 2 + data->player->y;
	length = 10;
	if (!data->mlx->minimap_player_img)
		data->mlx->minimap_player_img = create_player_image(data, length);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->mlx->minimap_player_img, x_coord, y_coord);
	create_fov(data, x_coord, y_coord);
	return (0);
}
