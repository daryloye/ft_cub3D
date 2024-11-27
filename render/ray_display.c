/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:00:29 by daong             #+#    #+#             */
/*   Updated: 2024/11/27 14:56:31 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	copy_texture_to_display(t_data *data, t_img texture, double *ray, double height)
{
	char	*src;
	char	*dst;
	double	y_inc;
	double	y;
	int		y_start;

	y_inc = data->texture->img_pix / height / 2;
	y_start = data->mlx->display_size_y / 2 - height - 1;
	y = -1;
	while (++y < 2 * height)
	{
		src = texture.addr
			+ (int)(y * y_inc) * texture.line_length
			+ (int)ray[X_PIX] * texture.bits_per_pixel / 8;
		dst = data->display->active.addr
			+ (int)(y + y_start) * data->display->active.line_length
			+ (int)ray[X_PIX] * data->display->active.bits_per_pixel / 8;
		*(unsigned int *)dst = *(unsigned int *)src;
	}
	return ;
}

/**
 * @brief Takes data on the wall height and the wall texture, and renders the wall onto the mlx display
 * 
 * @param data 
 * @param ray 
 * @param height 
 */
void	render_wall(t_data *data, double *ray, double ray_angle)
{
	double	height;

	// ISSUE: FISH EYE EFFECT
	double corrected_dist = ray[RAY_DIST] * cos(ray_angle - data->player->rot_deg);
	height = data->display->max_wall_height_pix
    - (corrected_dist - data->display->min_dist_to_wall) * 100;

	// put pixels from (y_center - height) to (y_center + height)
	if (ray[RAY_DIR] == NORTH)
		copy_texture_to_display(data, data->texture->north, ray, height);
	if (ray[RAY_DIR] == SOUTH)
		copy_texture_to_display(data, data->texture->south, ray, height);
	if (ray[RAY_DIR] == EAST)
		copy_texture_to_display(data, data->texture->east, ray, height);
	if (ray[RAY_DIR] == WEST)
		copy_texture_to_display(data, data->texture->west, ray, height);
	return ;
}
