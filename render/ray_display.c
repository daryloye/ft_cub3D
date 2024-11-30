/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:00:29 by daong             #+#    #+#             */
/*   Updated: 2024/11/30 19:23:07 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	copy_texture_to_display(t_data *data, t_img texture,
	double *ray, double img_x)
{
	char	*src;
	char	*dst;
	double	y_inc;
	double	y;
	int		y_start;

	y_inc = data->texture->img_pix / ray[HEIGHT] / 2;
	y_start = data->mlx->display_size_y / 2 - ray[HEIGHT];
	y = -1;
	while (++y < 2 * ray[HEIGHT])
	{
		src = texture.addr
			+ (int)(y * y_inc)*texture.line_length
			+ (int)fmod(img_x, data->texture->img_pix)
			* texture.bits_per_pixel / 8;
		dst = data->display->active.addr
			+ (int)(y + y_start)*data->display->active.line_length
			+ (int)ray[X_PIX] * data->display->active.bits_per_pixel / 8;
		*(unsigned int *)dst = *(unsigned int *)src;
	}
	return ;
}

// static void copy_texture_to_display(t_data *data, t_img texture, double *ray)
// {
// 	char	*src;
// 	char	*dst;

// 	double	y_disp;
// 	double	y_inc;
// 	int		y_disp_center;
// 	int		y_img_center;

// 	y_img_center = data->texture->img_pix / 2;
// 	y_disp_center = data->mlx->display_size_y / 2;
// 	y_inc = data->texture->img_pix / ray[HEIGHT];

// 	y_disp = -1;
// 	while (++y_disp < y_disp_center && y_disp < ray[HEIGHT])
// 	{
// 		src = texture.addr
// 			+ (int)(y_disp * y_inc)*texture.line_length
// 			+ (int)fmod(ray[END_X], data->texture->img_pix)
// 			* texture.bits_per_pixel / 8;
// 		dst = data->display->active.addr
// 			+ (int)(y_disp)*data->display->active.line_length
// 			+ (int)ray[X_PIX] * data->display->active.bits_per_pixel / 8;
// 		*(unsigned int *)dst = *(unsigned int *)src;
// 	}
// }

/**
 * @brief Takes data on the wall height and the wall texture,
 * and renders the wall onto the mlx display
 * 
 * @param data 
 * @param ray 
 * @param height 
 */
void	render_wall(t_data *data, double *ray, double ray_angle)
{
	double	max_height;
	double	angle_offset;
	double	adj_dist;

	max_height = data->mlx->display_size_y / 2;
	angle_offset = ray_angle - data->player->rot_deg;
    if (angle_offset > PI)
        angle_offset -= 2 * PI;
    else if (angle_offset < -PI)
        angle_offset += 2 * PI;
    adj_dist = ray[RAY_DIST] * cos(angle_offset);
	if (adj_dist < 0.1)
		adj_dist = 0.1;
    ray[HEIGHT] = max_height / adj_dist;
	if (ray[RAY_DIR] == NORTH)
		copy_texture_to_display(data, data->texture->north, ray, ray[END_X]);
	if (ray[RAY_DIR] == SOUTH)
		copy_texture_to_display(data, data->texture->south, ray, ray[END_X]);
	if (ray[RAY_DIR] == EAST)
		copy_texture_to_display(data, data->texture->east, ray, ray[END_Y]);
	if (ray[RAY_DIR] == WEST)
		copy_texture_to_display(data, data->texture->west, ray, ray[END_Y]);
	return ;
}
