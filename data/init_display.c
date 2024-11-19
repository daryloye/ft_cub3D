/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:40:29 by daong             #+#    #+#             */
/*   Updated: 2024/11/19 19:53:51 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief init display struct for ./render folder
 * 
 * @return t_display* 
 */
t_display	*init_display(void)
{
	t_display	*display;

	display = ft_calloc(sizeof(t_display), 1);
	if (!display)
		return (NULL);
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
	if (mlx->mlx_ptr && display->img.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, display->img.img_ptr);
	if (display)
		free(display);
	return ;
}
