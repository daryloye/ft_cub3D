/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:43:41 by daong             #+#    #+#             */
/*   Updated: 2024/10/27 19:27:34 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Create a rgb object from int_array[3]
 * 
 * @param rgb 
 * @return int 
 */
static int	create_rgb(int *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

/**
 * @brief init texture struct
 * 
 * @return t_texture* 
 */
t_texture	*init_texture(void)
{
	t_texture	*texture;

	texture = ft_calloc(sizeof(t_texture), 1);
	if (!texture)
		return (NULL);

	texture->north_texture = ft_strdup("");
	texture->south_texture = ft_strdup("");
	texture->west_texture = ft_strdup("");
	texture->east_texture = ft_strdup("");
	
	int f_color[3] = {255, 0, 0};
	texture->floor_color = create_rgb(f_color);

	int	c_color[3] = {0, 255, 255};
	texture->ceiling_color = create_rgb(c_color);
	
	return (texture);
}

/**
 * @brief clean texture struct
 * 
 * @param texture 
 */
void	clean_texture(t_texture *texture)
{
	if (texture->north_texture)
		free(texture->north_texture);
	if (texture->south_texture)
		free(texture->south_texture);
	if (texture->west_texture)
		free(texture->west_texture);
	if (texture->floor_color)
		free(texture->east_texture);
	if (texture)
		free(texture);
	return ;
}
