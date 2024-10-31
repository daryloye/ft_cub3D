/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:39:23 by daong             #+#    #+#             */
/*   Updated: 2024/10/31 14:16:43 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief init mlx struct
 * 
 * @return t_mlx* 
 */
t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = ft_calloc(sizeof(t_mlx), 1);
	if (!mlx)
		return (NULL);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (NULL);
	mlx_get_screen_size(mlx->mlx_ptr, &(mlx->display_size_x),
		&(mlx->display_size_y));
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->display_size_x,
			mlx->display_size_y, "cub3D");
	if (!mlx->win_ptr)
		return (NULL);
	mlx->horizon_height = mlx->display_size_y / 2;
	return (mlx);
}

/**
 * @brief clean mlx struct
 * 
 * @param mlx 
 */
void	clean_mlx(t_mlx *mlx)
{
	if (mlx->mlx_ptr && mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	if (mlx)
		free(mlx);
	return ;
}
