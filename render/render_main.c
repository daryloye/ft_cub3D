/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:32:33 by daong             #+#    #+#             */
/*   Updated: 2024/11/22 01:56:05 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief init fov data for player position and angles to walls
 * 
 * @param data 
 */
static int	render_fov(t_data *data)
{
	double	ray_angle;
	int		x;

	printf("fov_deg = %.2f\n", data->player->fov_deg);
	printf("min_dist = %.2f\n", data->display->min_dist_to_wall);
	x = data->mlx->display_size_x / 2;
	while (++x < data->mlx->display_size_x)
	{
		// convert pix to distance??
		ray_angle = data->player->rot_deg + (x * data->display->coord_to_pix_scale / data->display->min_dist_to_wall);
		//printf("ray_angle = %.2f\n", ray_angle);
		create_single_ray(data, ray_angle, x);
	}
	return (0);
}

/**
 * @brief Cleans data and exits program if anything goes wrong in render
 * 
 * @param data 
 */
static void	render_error(t_data *data)
{
	ft_printf("Error\n%s\n", strerror(errno));
	clean_data(data);
	exit(EXIT_FAILURE);
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
	if (render_minimap(data) == 1 || render_fov(data) == 1)
		render_error(data);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->display->active.img_ptr, 0, 0);
	if (data->keys[M] == 1)
		mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->minimap->active.img_ptr, 0, 0);
	return ;
}
