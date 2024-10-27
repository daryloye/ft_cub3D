/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:39:23 by daong             #+#    #+#             */
/*   Updated: 2024/10/27 12:17:01 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Init mlx struct
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
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, DISPLAY_X, DISPLAY_Y, "./cub3D");
	if (!mlx->win_ptr)
		return (NULL);
	return (mlx);
}	
/**
 * @brief Clean mlx struct
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
