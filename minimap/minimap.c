/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:54:58 by daong             #+#    #+#             */
/*   Updated: 2024/11/09 16:43:23 by daong            ###   ########.fr       */
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
	data->minimap->wall_length = get_wall_length(data);
	if (minimap_background(data) == 1)
		return (1);
	if (minimap_player(data) == 1)
		return (1);
	return (0);
}
