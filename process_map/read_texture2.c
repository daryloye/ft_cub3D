/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:23:03 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/08 08:26:51 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	set_texture(void *mlx_ptr, char *file_path, t_img *texture)
{
	texture->img_ptr = mlx_xpm_file_to_image(mlx_ptr, file_path,
			&texture->width, &texture->height);
	if (!texture->img_ptr)
		return (print_error("Failed to load texture"), 1);
	texture->addr = mlx_get_data_addr(texture->img_ptr,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (!texture->addr)
		return (print_error("Failed to get data address for texture"), 1);
	return (0);
}
