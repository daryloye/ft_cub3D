/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:31:38 by daong             #+#    #+#             */
/*   Updated: 2024/12/04 18:37:55 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	copy_image_to_display(t_data *data, t_img texture)
{
	char	*src;
	char	*dst;
	int		y;
	int		x;

	y = -1;
	while (++y < texture.width)
	{
		x = -1;
		while (++x < texture.width)
		{
			src = texture.addr
				+ (y + ((int)data->display->sprite_inc * texture.width))
				*texture.line_length
				+ x * texture.bits_per_pixel / 8;
			if (strcmp(src, "") == 0)	// forbidden function
				continue ;
			dst = data->display->active.addr
				+ y * data->display->active.line_length
				+ (x + data->mlx->display_size_x - texture.width)
				*data->display->active.bits_per_pixel / 8;
			*(unsigned int *)dst = *(unsigned int *)src;
		}
	}
	return ;
}

// static void	pause_image(t_data *data, t_img texture)
// {
// 	char	*src;
// 	char	*dst;
// 	int		y;
// 	int		x;

// 	y = -1;
// 	while (++y < texture.width)
// 	{
// 		x = -1;
// 		while (++x < texture.width)
// 		{
// 			src = texture.addr
// 				+ (y + ((int)data->display->sprite_inc * texture.width))
// 				*texture.line_length
// 				+ x * texture.bits_per_pixel / 8;
// 			if (strcmp(src, "") == 0)	// forbidden function
// 				continue ;
// 			dst = data->display->active.addr
// 				+ (y + 10) * data->display->active.line_length
// 				+ (x + 50)
// 				*data->display->active.bits_per_pixel / 8;
// 			*(unsigned int *)dst = *(unsigned int *)src;
// 		}
// 	}
// 	return ;
// }

/**
 * @brief renders sprite gif according to each action
 * 
 * @param data 
 */
void	render_sprite(t_data *data)
{
	if (data->keys[P] == 1)
	{
		data->display->sprite_inc = fmod(data->display->sprite_inc + 1,
			data->display->sprite_frames);
		copy_image_to_display(data, data->display->sprite[PAUSE]);
		return ;
	}
	if (data->keys[LEFT_ARROW] == 1)
		copy_image_to_display(data, data->display->sprite[ROTATE_LEFT]);
	else if (data->keys[RIGHT_ARROW] == 1)
		copy_image_to_display(data, data->display->sprite[ROTATE_RIGHT]);
	else
		copy_image_to_display(data, data->display->sprite[REST]);
	data->display->sprite_inc = fmod(data->display->sprite_inc + 1,
			data->display->sprite_frames);
	return ;
}

static int	create_sprite_img(t_data *data, t_display *display, int sprite_index, char *path)
{
	t_img	sprite;

	sprite.img_ptr = mlx_xpm_file_to_image(data->mlx->mlx_ptr, path,
			&(sprite.width), &(sprite.height));
	if (!(sprite.img_ptr))
		return (print_error("Sprite init failed"), 1);
	sprite.addr = mlx_get_data_addr(sprite.img_ptr,
			&(sprite.bits_per_pixel), &(sprite.line_length),
			&(sprite.endian));
	if (!sprite.addr)
		return (print_error("Failed to get data address for sprite"), 1);
	display->sprite[sprite_index] = sprite;
	return (0);
}

/**
 * @brief init sprite textures to display struct
 * 
 * @param data 
 * @param display 
 * @return int 
 */
int	init_sprite(t_data *data, t_display *display)
{
	int	err;

	display->sprite_inc = 0.0;
	display->sprite_frames = 20;
	err = 0;
	err |= create_sprite_img(data, display, REST, "sprite/rest.xpm");
	err |= create_sprite_img(data, display, ROTATE_LEFT, "sprite/rotate_left.xpm");
	err |= create_sprite_img(data, display, ROTATE_RIGHT, "sprite/rotate_right.xpm");
	err |= create_sprite_img(data, display, PAUSE, "sprite/pause.xpm");
	return (err);
}
