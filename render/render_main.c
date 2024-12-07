/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:32:33 by daong             #+#    #+#             */
/*   Updated: 2024/12/07 09:41:48 by daong            ###   ########.fr       */
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
	double	angle_step;
	int		x;

	angle_step = data->player->fov_deg / data->mlx->display_size_x;
	x = -1;
	while (++x < data->mlx->display_size_x)
	{
		ray_angle = data->player->rot_deg - (data->player->fov_deg / 2)
			+ (x * angle_step);
		ray_angle = fmod(ray_angle, PI * 2);
		if (create_single_ray(data, ray_angle, x) != 0)
			return (1);
	}
	return (0);
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
	render_sprite(data);
	wait_fps(data);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->display->active.img_ptr, 0, 0);
	if (data->keys[KEY_MAP] == 1)
		mlx_put_image_to_window(data->mlx->mlx_ptr,
			data->mlx->win_ptr, data->minimap->active.img_ptr, 0, 0);
	return ;
}
