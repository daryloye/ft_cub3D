/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:32:33 by daong             #+#    #+#             */
/*   Updated: 2024/11/14 22:51:25 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	if (render_background(data) == 1)
		render_error(data);
	if (render_minimap(data) == 1)
		render_error(data);
	if (render_fov(data) == 1)
		render_error(data);
	if (data->keys[M] == 1)
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win_ptr, data->minimap->img.img_ptr, 0, 0);
	return ;
}
