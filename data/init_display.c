/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:40:29 by daong             #+#    #+#             */
/*   Updated: 2024/12/04 18:38:06 by daong            ###   ########.fr       */
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
	init_sprite(data, display);
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
	int	i;

	if (mlx->mlx_ptr && display->background.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, display->background.img_ptr);
	if (mlx->mlx_ptr && display->active.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, display->active.img_ptr);
	i = -1;
	while (++i < SPRITE_COUNT)
	{
		if (mlx->mlx_ptr && display->sprite[i].img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, display->sprite[i].img_ptr);
	}
	if (display)
		free(display);
	return ;
}
