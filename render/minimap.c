/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:54:58 by daong             #+#    #+#             */
/*   Updated: 2024/11/06 01:41:04 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	minimap_player(t_data *data)
{
	void	*img_ptr;
	int		img_pix;
	float	x_coord;
	float	y_coord;
	
	x_coord = data->mlx->display_size_x / 2 + data->player->x;
	y_coord = data->mlx->display_size_y / 2 + data->player->y;
	img_pix = 100;
	img_ptr = mlx_xpm_file_to_image(data->mlx->mlx_ptr, "img/minimap_wall.xpm", &img_pix, &img_pix);
	if (!img_ptr)
		return (1);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, img_ptr, x_coord, y_coord);
	mlx_destroy_image(data->mlx->mlx_ptr, img_ptr);
	return (0);
}

static int	minimap_walls(t_data *data)
{
	void	*img_ptr;
	int		img_pix;

	img_pix = 100;
	img_ptr = mlx_xpm_file_to_image(data->mlx->mlx_ptr, "img/minimap_wall.xpm", &img_pix, &img_pix);
	if (!img_ptr)
		return (1);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, img_ptr, 0, 0);
	mlx_destroy_image(data->mlx->mlx_ptr, img_ptr);
	return (0);
}

/**
 * @brief renders 2D minimap on top left of window
 * 
 * @param data 
 * @return int 
 */
int	render_minimap(t_data *data)
{
	if (minimap_walls(data) == 1 || minimap_player(data) == 1)
		return (1);
	return (0);
}
