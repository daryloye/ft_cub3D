/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:10:42 by daong             #+#    #+#             */
/*   Updated: 2024/10/27 12:17:29 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	key_press(int key, t_data *data)
{
	if (key == 65307)
		mlx_loop_end(data->mlx->mlx_ptr);
	//else if (key == 'w' || key == 'a' || key == 's' || key == 'd')
		//do_movements(data, key);
	return (1);
}

static int	handle_resize(t_data *data)
{
	if (data)
		return (0);
	//render(data);
	return (1);
}

static int	handle_close(t_data *data)
{
	mlx_loop_end(data->mlx->mlx_ptr);
	return (1);
}

/**
 * @brief init hooks
 * 
 * @param data 
 */
void	init_hooks(t_data *data)
{
	mlx_key_hook(data->mlx->win_ptr, key_press, data);
	mlx_hook(data->mlx->win_ptr, 15, 1L << 16, handle_resize, data);
	mlx_hook(data->mlx->win_ptr, 22, 1L << 17, handle_resize, data);
	mlx_hook(data->mlx->win_ptr, 17, 0, handle_close, data);
	return ;
}
