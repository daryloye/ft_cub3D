/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:10:42 by daong             #+#    #+#             */
/*   Updated: 2024/12/04 12:05:27 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	key_press(int key, t_data *data)
{
	if (key == 65307)
		mlx_loop_end(data->mlx->mlx_ptr);
	if (key == 'w')
		data->keys[W] = 1;
	if (key == 'a')
		data->keys[A] = 1;
	if (key == 's')
		data->keys[S] = 1;
	if (key == 'd')
		data->keys[D] = 1;
	if (key == 65361)
		data->keys[LEFT_ARROW] = 1;
	if (key == 65363)
		data->keys[RIGHT_ARROW] = 1;
	if (key == 'm')
		data->keys[M] *= -1;
	if (key == 'p')
		data->keys[P] *= -1;
	if (key == 'o')
		handle_doors(data);
	return (1);
}

static int	key_release(int key, t_data *data)
{
	if (key == 'w')
		data->keys[W] = 0;
	if (key == 'a')
		data->keys[A] = 0;
	if (key == 's')
		data->keys[S] = 0;
	if (key == 'd')
		data->keys[D] = 0;
	if (key == 65361)
		data->keys[LEFT_ARROW] = 0;
	if (key == 65363)
		data->keys[RIGHT_ARROW] = 0;
	return (1);
}

static int	handle_resize(t_data *data)
{
	render(data);
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
	data->keys[M] = -1;
	data->keys[P] = -1;
	data->keys[O] = -1;
	mlx_hook(data->mlx->win_ptr, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win_ptr, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win_ptr, 15, 1L << 16, handle_resize, data);
	mlx_hook(data->mlx->win_ptr, 22, 1L << 17, handle_resize, data);
	mlx_hook(data->mlx->win_ptr, 17, 0, handle_close, data);
	return ;
}
