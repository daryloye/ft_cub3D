/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:54:58 by daong             #+#    #+#             */
/*   Updated: 2024/11/02 19:17:44 by daong            ###   ########.fr       */
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
	void	*img_ptr;
	int		wall_pix;

	wall_pix = 100;
	img_ptr = mlx_xpm_file_to_image(data->mlx->mlx_ptr, "img/minimap_wall.xpm", &wall_pix, &wall_pix);
	if (!img_ptr)
		return (1);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, img_ptr, 0, 0);
	mlx_destroy_image(data->mlx->mlx_ptr, img_ptr);
	return (0);
}
