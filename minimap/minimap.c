/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:54:58 by daong             #+#    #+#             */
/*   Updated: 2024/12/04 10:51:20 by daong            ###   ########.fr       */
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

	if (data->minimap->display_scale == 0)
		print_error("display scale cannot be 0");
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
				(data->map_size_x - 1) * data->minimap->wall_length,
				data->map_size_y * data->minimap->wall_length);
		if (!data->minimap->background.img_ptr)
			return (1);
		minimap_background(data);
	}
	if (!data->minimap->active.img_ptr)
	{
		data->minimap->active = init_blank_image(data,
				(data->map_size_x - 1) * data->minimap->wall_length,
				data->map_size_y * data->minimap->wall_length);
		if (!data->minimap->active.img_ptr)
			return (1);
	}
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
void	dda_minimap(t_data *data, double *ray)
{
	double	x_inc;
	double	y_inc;
	int		steps;
	double	pos[POS_COUNT];

	pos[START_X] = ray[START_X] * data->minimap->wall_length;
	pos[START_Y] = ray[START_Y] * data->minimap->wall_length;
	pos[END_X] = ray[END_X] * data->minimap->wall_length;
	pos[END_Y] = ray[END_Y] * data->minimap->wall_length;
	steps = ft_max(abs((int)(pos[END_X] - pos[START_X])),
			abs((int)(pos[END_Y] - pos[START_Y])));
	x_inc = (pos[END_X] - pos[START_X]);
	y_inc = (pos[END_Y] - pos[START_Y]);
	if (steps != 0)
	{
		x_inc /= (double)steps;
		y_inc /= (double)steps;
	}
	while (steps-- > 0)
	{
		ft_mlx_pixel_put(data->minimap->active, round(pos[START_X]),
			round(pos[START_Y]), trgb(0, 0, 255, 0));
		pos[START_X] += x_inc;
		pos[START_Y] += y_inc;
	}
}
