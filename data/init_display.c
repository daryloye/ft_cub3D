/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:40:29 by daong             #+#    #+#             */
/*   Updated: 2024/12/01 14:06:53 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_sprite(t_data *data, t_display *display)
{
	int		i;
	char	*i_str;
	char	*path1;
	char	*path2;

	display->sprite_inc = 0.0;
	i = -1;
	while (++i < SPRITE_COUNT)
	{
		i_str = ft_itoa(i);
		path1 = ft_strjoin("sprite/sprite_", i_str);
		path2 = ft_strjoin(path1, ".xpm");
		display->sprite[i].img_ptr = mlx_xpm_file_to_image(data->mlx->mlx_ptr,
				path2, &(display->sprite[i].width), &(display->sprite[i].height));
		if (!(display->sprite[i].img_ptr))
			print_error("Sprite init failed");
		display->sprite[i].addr = mlx_get_data_addr(display->sprite[i].img_ptr,
				&(display->sprite[i].bits_per_pixel), &(display->sprite[i].line_length),
				&(display->sprite[i].endian));
		if (!display->sprite[i].addr)
			print_error("Failed to get data address for sprite");
		free(i_str);
		free(path1);
		free(path2);
	}
	return ;
}

/**
 * @brief init display struct for ./render folder
 * 
 * @return t_display* 
 */
t_display	*init_display(t_data *data)
{
	t_display	*display;

	display = ft_calloc(sizeof(t_display), 1);
	if (!display)
		return (NULL);
	display->min_dist_to_wall = ((data->mlx->display_size_x / 2)
			/ tan(data->player->fov_deg / 2)) / 20000;
	init_sprite(data, display);
	return (display);
}

/**
 * @brief destroy images used in ./render folder, clean display struct
 * 
 * @param display 
 * @param mlx 
 */
void	clean_display(t_display *display, t_mlx *mlx)
{
	int	i;

	if (mlx->mlx_ptr && display->background.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, display->background.img_ptr);
	if (mlx->mlx_ptr && display->active.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, display->active.img_ptr);
	i = -1;
	while (++i < SPRITE_COUNT)
	{
		if (mlx->mlx_ptr && display->sprite[i].img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, display->sprite[i].img_ptr);
	}
	if (display)
		free(display);
	return ;
}
