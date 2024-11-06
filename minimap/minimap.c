/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:54:58 by daong             #+#    #+#             */
/*   Updated: 2024/11/06 11:36:38 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief renders 2D minimap on top left of window
 * 
 * @param data 
 * @return int 
 */
int	render_minimap(t_data *data)
{
	if (minimap_background(data) == 1)
		return (1);
	if (minimap_player(data) == 1)
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
