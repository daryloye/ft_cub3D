/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:54:58 by daong             #+#    #+#             */
/*   Updated: 2024/11/07 03:26:47 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Get minimap wall length
 * Minimap scale is 1/2 of display size
 * Tries to fit minimap within the scale constriant
 * 
 * @param data 
 * @return int 
 */
static int	get_wall_length(t_data *data)
{
	int	scale;
	int	max_pix_x;
	int	max_pix_y;
	int	x_len;
	int	y_len;

	scale = 2;
	max_pix_x = data->mlx->display_size_x / scale;
	max_pix_y = data->mlx->display_size_y / scale;
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
	int	wall_length;

	wall_length = get_wall_length(data);
	if (minimap_background(data, wall_length) == 1)
		return (1);
	if (minimap_player(data, wall_length) == 1)
		return (1);
	return (0);
}

/**
 * @brief destroy images used in ./minimap folder
 * 
 * @param mlx 
 */
void	clean_minimap(t_mlx *mlx)
{
	if (mlx->mlx_ptr && mlx->minimap_wall_img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->minimap_wall_img);
	if (mlx->mlx_ptr && mlx->minimap_floor_img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->minimap_floor_img);
	if (mlx->mlx_ptr && mlx->minimap_player_img)
		mlx_destroy_image(mlx->mlx_ptr, mlx->minimap_player_img);
	return ;
}
