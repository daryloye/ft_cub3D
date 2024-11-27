/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:32:33 by daong             #+#    #+#             */
/*   Updated: 2024/11/27 18:04:39 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief finds angle and pixel pos of each ray, sends data to create_single_ray
 * 
 * @param data 
 * @return int 
 */
static int	render_fov(t_data *data)
{
	double	ray_angle;
	double	adj_side;
	int		x;
	int		center_x;

	adj_side = data->display->coord_to_pix_scale
		* data->display->min_dist_to_wall;
	center_x = data->mlx->display_size_x / 2;
	x = -1;
	while (++x <= center_x)
	{
		ray_angle = data->player->rot_deg - atan(x / adj_side);
		ray_angle = fmod(ray_angle, PI * 2);
		if (create_single_ray(data, ray_angle, center_x - x) != 0)
			return (1);
	}
	x--;
	while (++x < data->mlx->display_size_x)
	{
		ray_angle = data->player->rot_deg + atan((x - center_x) / adj_side);
		ray_angle = fmod(ray_angle, PI * 2);
		if (create_single_ray(data, ray_angle, x) != 0)
			return (1);
	}
	return (0);
}

static void	pause_image(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr,
		data->display->sprite[(int)data->display->sprite_inc].img_ptr,
		500, 300);
	data->display->sprite_inc = fmod(data->display->sprite_inc + 0.1,
			SPRITE_COUNT);
	mlx_string_put(data->mlx->mlx_ptr, data->mlx->win_ptr, 200, 200, 0,
		"PAUSED");
	return ;
}

/**
 * @brief Main render function. if error, calls render_error
 * 
 * @param data 
 */
void	render(t_data *data)
{
	init_display_images(data);
	ft_memcpy(data->display->active.addr, data->display->background.addr,
		data->mlx->display_size_y * data->display->background.line_length);
	render_minimap(data);
	render_fov(data);
	wait_fps(data);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->display->active.img_ptr, 0, 0);
	if (data->keys[P] == 1)
		pause_image(data);
	if (data->keys[M] == 1)
		mlx_put_image_to_window(data->mlx->mlx_ptr,
			data->mlx->win_ptr, data->minimap->active.img_ptr, 0, 0);
	return ;
}
