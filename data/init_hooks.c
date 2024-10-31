/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:10:42 by daong             #+#    #+#             */
/*   Updated: 2024/10/31 16:32:57 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	key_press(int key, t_data *data)
{
	printf("Key pressed: %d\n", key);
	if (key == 65307)
		mlx_loop_end(data->mlx->mlx_ptr);
	if (key == 'w')
		data->keys[0] = 1;
	if (key == 'a')
		data->keys[1] = 1;
	if (key == 's')
		data->keys[2] = 1;
	if (key == 'd')
		data->keys[3] = 1;
	if (key == 65361)
		data->keys[4] = 1;
	if (key == 65363)
		data->keys[5] = 1;
	return (1);
}

static int	key_release(int key, t_data *data)
{
	printf("Key released: %d\n", key);
	if (key == 'w')
		data->keys[0] = 0;
	if (key == 'a')
		data->keys[1] = 0;
	if (key == 's')
		data->keys[2] = 0;
	if (key == 'd')
		data->keys[3] = 0;
	if (key == 65361)
		data->keys[4] = 0;
	if (key == 65363)
		data->keys[5] = 0;
	return (1);
}

static int	handle_resize(t_data *data)
{
	if (data)
		return (0);
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
	mlx_hook(data->mlx->win_ptr, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win_ptr, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win_ptr, 15, 1L << 16, handle_resize, data);
	mlx_hook(data->mlx->win_ptr, 22, 1L << 17, handle_resize, data);
	mlx_hook(data->mlx->win_ptr, 17, 0, handle_close, data);
	return ;
}
