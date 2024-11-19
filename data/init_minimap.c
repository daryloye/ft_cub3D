/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:45:59 by daong             #+#    #+#             */
/*   Updated: 2024/11/19 19:54:05 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief init minimap struct for ./minimap folder
 * 
 * @return t_minimap* 
 */
t_minimap	*init_minimap(void)
{
	t_minimap	*minimap;

	minimap = ft_calloc(sizeof(t_minimap), 1);
	if (!minimap)
		return (NULL);
	minimap->display_scale = 3;
	minimap->player_length = 10;
	return (minimap);
}

/**
 * @brief destroy images used in ./minimap folder, clean minimap struct
 * 
 * @param minimap 
 * @param mlx 
 */
void	clean_minimap(t_minimap *minimap, t_mlx *mlx)
{
	if (mlx->mlx_ptr && minimap->img.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, minimap->img.img_ptr);
	if (minimap)
		free(minimap);
	return ;
}
