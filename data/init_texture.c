/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:43:41 by daong             #+#    #+#             */
/*   Updated: 2024/12/01 11:29:52 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	texture->img_pix = 128;
	return (texture);
}

/**
 * @brief clean texture struct
 * 
 * @param texture 
 */
void	clean_texture(t_texture *texture, t_mlx *mlx)
{
	if (mlx->mlx_ptr && texture->north.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, texture->north.img_ptr);
	if (mlx->mlx_ptr && texture->south.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, texture->south.img_ptr);
	if (mlx->mlx_ptr && texture->east.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, texture->east.img_ptr);
	if (mlx->mlx_ptr && texture->west.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, texture->west.img_ptr);
	if (mlx->mlx_ptr && texture->door.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, texture->door.img_ptr);
	if (texture->north_texture)
		free(texture->north_texture);
	if (texture->south_texture)
		free(texture->south_texture);
	if (texture->west_texture)
		free(texture->west_texture);
	if (texture->east_texture)
		free(texture->east_texture);
	if (texture)
		free(texture);
	return ;
}
