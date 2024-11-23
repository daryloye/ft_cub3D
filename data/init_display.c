/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:40:29 by daong             #+#    #+#             */
/*   Updated: 2024/11/23 14:47:41 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief init display struct for ./render folder
 * 
 * @return t_display* 
 */
t_display	*init_display(t_data *data)
{
	t_display	*display;

	display = ft_calloc(sizeof(t_display), 1);
	if (!display)
		return (NULL);
	display->coord_to_pix_scale = 10000;
	display->min_dist_to_wall = ((data->mlx->display_size_x / 2)
			/ tan(data->player->fov_deg)) / display->coord_to_pix_scale;
	display->max_wall_height_pix = 300;
	return (display);
}

/**
 * @brief destroy images used in ./render folder, clean display struct
 * 
 * @param display 
 * @param mlx 
 */
void	clean_display(t_display *display, t_mlx *mlx)
{
	if (mlx->mlx_ptr && display->background.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, display->background.img_ptr);
	if (mlx->mlx_ptr && display->active.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, display->active.img_ptr);
	if (display)
		free(display);
	return ;
}
