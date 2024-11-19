/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:54:58 by daong             #+#    #+#             */
/*   Updated: 2024/11/19 22:37:29 by daong            ###   ########.fr       */
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
	if (!data->minimap->background.img_ptr)
	{
		data->minimap->wall_length = get_wall_length(data);
		data->minimap->background = init_blank_image(data,
				data->map_size_x * data->minimap->wall_length,
				data->map_size_y * data->minimap->wall_length);
		minimap_background(data);
	}
	if (!data->minimap->active.img_ptr)
		data->minimap->active = init_blank_image(data,
				data->map_size_x * data->minimap->wall_length,
				data->map_size_y * data->minimap->wall_length);
	ft_memcpy(data->minimap->active.addr,
		data->minimap->background.addr, data->map_size_y
		* data->minimap->wall_length
		* data->minimap->background.line_length);
	minimap_player(data);
	return (0);
}

/**
 * @brief dda for minimap
 * 
 * @param img 
 * @param pos 
 * @param color 
 */
void	dda_minimap(t_data *data, double pos[POS_COUNT], int color)
{
	double	Xinc;
	double	Yinc;
	int		steps;
	int		i;

	i = -1;
	while (++i < 4)
		pos[i] *= data->minimap->wall_length;
	if (abs((int)(pos[END_X] - pos[START_X])) > abs((int)(pos[END_Y] - pos[START_Y])))
		steps = abs((int)(pos[END_X] - pos[START_X]));
	else
		steps = abs((int)(pos[END_Y] - pos[START_Y]));
    Xinc = (pos[END_X] - pos[START_X]) / (double)steps; 
    Yinc = (pos[END_Y] - pos[START_Y]) / (double)steps; 
	i = -1;
    while (++i < steps)
	{ 
        ft_mlx_pixel_put(data->minimap->active, round(pos[START_X]), round(pos[START_Y]), color);
        pos[START_X] += Xinc;
		pos[START_Y] += Yinc;
	}
	return ;
}
