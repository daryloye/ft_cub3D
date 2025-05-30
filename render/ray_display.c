/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:00:29 by daong             #+#    #+#             */
/*   Updated: 2024/12/04 13:31:01 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	copy_texture_to_display(t_data *data, t_img texture,
	double *ray, double img_x)
{
	char	*src;
	char	*dst;
	double	y_inc;
	int		y;
	int		offset;

	y_inc = texture.height / (ray[HEIGHT] * 2);
	offset = ray[HEIGHT] - data->mlx->display_size_y / 2;
	y = -1;
	while (++y < ft_min(2 * ray[HEIGHT], data->mlx->display_size_y))
	{
		src = texture.addr
			+ (int)((y + ft_max(offset, 0)) * y_inc)*texture.line_length
			+ (int)(fmod(img_x, 1.0) * texture.width)*texture.bits_per_pixel
			/ 8;
		dst = data->display->active.addr
			+ (int)(y - ft_min(offset, 0))*data->display->active.line_length
			+ (int)ray[X_PIX] * data->display->active.bits_per_pixel / 8;
		*(unsigned int *)dst = *(unsigned int *)src;
	}
	return ;
}

/**
 * @brief find height of wall
 * 
 * @param data 
 * @param ray 
 */
static void	get_height(t_data *data, double *ray)
{
	double	max_height;
	double	angle_offset;
	double	adj_dist;

	max_height = data->mlx->display_size_y / 2;
	angle_offset = ray[ANGLE] - data->player->rot_deg;
	if (angle_offset > PI)
		angle_offset -= 2 * PI;
	else if (angle_offset < -PI)
		angle_offset += 2 * PI;
	adj_dist = ray[RAY_DIST] * cos(angle_offset);
	if (adj_dist < 0.1)
		adj_dist = 0.1;
	ray[HEIGHT] = max_height / adj_dist;
	return ;
}

/**
 * @brief Takes data on the wall height and the wall texture,
 * and renders the wall onto the mlx display
 * 
 * @param data 
 * @param ray 
 * @param height 
 */
void	render_wall(t_data *data, double *ray)
{
	get_height(data, ray);
	if (ray[RAY_DIR] == NORTH)
		copy_texture_to_display(data, data->texture->north, ray, ray[END_X]);
	else if (ray[RAY_DIR] == SOUTH)
		copy_texture_to_display(data, data->texture->south, ray, ray[END_X]);
	else if (ray[RAY_DIR] == EAST)
		copy_texture_to_display(data, data->texture->east, ray, ray[END_Y]);
	else if (ray[RAY_DIR] == WEST)
		copy_texture_to_display(data, data->texture->west, ray, ray[END_Y]);
	else if (ray[RAY_DIR] == DOOR_NS)
		copy_texture_to_display(data, data->texture->door, ray, ray[END_X]);
	else if (ray[RAY_DIR] == DOOR_EW)
		copy_texture_to_display(data, data->texture->door, ray, ray[END_Y]);
	return ;
}
