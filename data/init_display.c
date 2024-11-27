/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:40:29 by daong             #+#    #+#             */
/*   Updated: 2024/11/27 18:35:33 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_sprite(t_data *data, t_display *display)
{
	int			i;
	char		*i_str;
	char		*path1;
	char		*path2;

	display->sprite_pix = 150;
	display->sprite_inc = 0.0;
	i = -1;
	while (++i < SPRITE_COUNT)
	{
		i_str = ft_itoa(i);
		path1 = ft_strjoin("sprite/sprite_", i_str);
		path2 = ft_strjoin(path1, ".xpm");
		display->sprite[i].img_ptr = mlx_xpm_file_to_image(data->mlx->mlx_ptr,
				path2, &(display->sprite_pix), &(display->sprite_pix));
		if (!(display->sprite[i].img_ptr))
			print_error("Sprite init failed");
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
	display->coord_to_pix_scale = 20000;
	display->min_dist_to_wall = ((data->mlx->display_size_x / 2)
			/ tan(data->player->fov_deg)) / display->coord_to_pix_scale;
	display->max_wall_height_pix = data->mlx->display_size_y / 2;
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
