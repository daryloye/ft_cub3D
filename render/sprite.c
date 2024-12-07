/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:31:38 by daong             #+#    #+#             */
/*   Updated: 2024/12/07 10:13:25 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_sprite_index(t_data *data, t_img texture)
{
	int	frames;
	int	sprite_index;

	frames = texture.height / texture.width;
	sprite_index = fmod(data->display->sprite_inc, frames);
	data->display->sprite_inc++;
	return (sprite_index);
}

static void	copy_image_to_display(t_data *data, t_img texture)
{
	char	*src;
	char	*dst;
	int		y;
	int		x;
	int		sprite_index;

	sprite_index = get_sprite_index(data, texture);
	y = -1;
	while (++y < texture.width)
	{
		x = -1;
		while (++x < texture.width)
		{
			src = texture.addr
				+ (y + (sprite_index * texture.width))
				*texture.line_length + x
				* texture.bits_per_pixel / 8;
			dst = data->display->active.addr + y
				*data->display->active.line_length
				+ (x + data->mlx->display_size_x - texture.width)
				*data->display->active.bits_per_pixel / 8;
			*(unsigned int *)dst = *(unsigned int *)src;
		}
	}
	return ;
}

/**
 * @brief renders sprite gif according to each action
 * 
 * @param data 
 */
void	render_sprite(t_data *data)
{
	if (data->keys[KEY_SPRITE] == 1)
	{
		if (data->keys[KEY_PAUSE] == 1)
			copy_image_to_display(data, data->display->sprite[SP_PAUSE]);
		else if (data->keys[W] == 1 || data->keys[A] == 1
			|| data->keys[S] == 1 || data->keys[D] == 1)
			copy_image_to_display(data, data->display->sprite[SP_MOVE]);
		else if (data->keys[LEFT_ARROW] == 1)
			copy_image_to_display(data, data->display->sprite[SP_ROT_LEFT]);
		else if (data->keys[RIGHT_ARROW] == 1)
			copy_image_to_display(data, data->display->sprite[SP_ROT_RIGHT]);
		else
			copy_image_to_display(data, data->display->sprite[SP_REST]);
	}
	return ;
}

static int	create_sprite_img(t_data *data, t_display *display,
		int sprite_index, char *path)
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
	err = 0;
	err |= create_sprite_img(data, display, SP_REST, "sprite/42_rest.xpm");
	err |= create_sprite_img(data, display, SP_MOVE, "sprite/42_move.xpm");
	err |= create_sprite_img(data, display, SP_ROT_LEFT, "sprite/42_left.xpm");
	err |= create_sprite_img(data, display, SP_ROT_RIGHT, "sprite/42_right.xpm");
	err |= create_sprite_img(data, display, SP_PAUSE, "sprite/42_pause.xpm");
	return (err);
}
