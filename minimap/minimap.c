/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:54:58 by daong             #+#    #+#             */
/*   Updated: 2024/11/11 00:58:20 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Get minimap wall length
 * Minimap scale is 1/3 of display size
 * Tries to fit minimap within the scale constriant
 * 
 * @param data 
 * @return int 
 */
static int	get_wall_length(t_data *data)
{
	int	max_pix_x;
	int	max_pix_y;
	int	x_len;
	int	y_len;

	max_pix_x = data->mlx->display_size_x / data->minimap->display_scale;
	max_pix_y = data->mlx->display_size_y / data->minimap->display_scale;
	x_len = max_pix_x / data->map_size_x;
	y_len = max_pix_y / data->map_size_y;
	if (x_len < y_len)
		return (x_len);
	else
		return (y_len);
}

/**
 * @brief renders 2D minimap on top left of window
 * 
 * @param data 
 * @return int 
 */
int	render_minimap(t_data *data)
{
	if (!data->minimap->img.img_ptr)
	{
		data->minimap->wall_length = get_wall_length(data);
		data->minimap->img = init_blank_image(data,
				data->map_size_x * data->minimap->wall_length, 
				data->map_size_y * data->minimap->wall_length);
	}
	minimap_background(data);
	minimap_player(data);
	minimap_fov(data);
	if (data->keys[M] == 1)
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, data->minimap->img.img_ptr, 0, 0);
	return (0);
}
