/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:32:33 by daong             #+#    #+#             */
/*   Updated: 2024/11/19 20:42:01 by daong            ###   ########.fr       */
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
	int		color;

	color = create_trgb(0, 0, 255, 0);

	ray_angle = data->player->rot_deg;

	for (ray_angle = data->player->rot_deg - data->player->fov_deg; ray_angle < data->player->rot_deg + data->player->fov_deg; ray_angle += 0.1)
		create_single_ray(data, ray_angle, color);
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
	if (!data->display->img.img_ptr)
		data->display->img = init_blank_image(data, 
			data->mlx->display_size_x,
			data->mlx->display_size_y);
	if (render_background(data) == 1)
		render_error(data);
	if (render_minimap(data) == 1)
		render_error(data);
	if (render_fov(data) == 1)
		render_error(data);
	mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->display->img.img_ptr, 0, 0);
	if (data->keys[M] == 1)
		mlx_put_image_to_window(data->mlx->mlx_ptr,
		data->mlx->win_ptr, data->minimap->img.img_ptr, 0, 0);
	return ;
}
