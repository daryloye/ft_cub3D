/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:41:25 by daong             #+#    #+#             */
/*   Updated: 2024/12/04 12:05:33 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief check if the new position is in a wall, else update the new position
 * 
 * @param data 
 * @param x 
 * @param y 
 */
static void	check_wall(t_data *data, double x, double y)
{
	double	x1;
	double	y1;
	double	min_dist;

	min_dist = 0.1;
	x1 = data->player->x_pos + x;
	y1 = data->player->y_pos + y;
	if (data->map[(int)(y1 - min_dist)][(int)(x1 - min_dist)] == WALL
		|| data->map[(int)(y1 - min_dist)][(int)(x1 + min_dist)] == WALL
		|| data->map[(int)(y1 + min_dist)][(int)(x1 - min_dist)] == WALL
		|| data->map[(int)(y1 + min_dist)][(int)(x1 + min_dist)] == WALL
		|| data->map[(int)(y1 - min_dist)][(int)(x1 - min_dist)] == DOORC
		|| data->map[(int)(y1 - min_dist)][(int)(x1 + min_dist)] == DOORC
		|| data->map[(int)(y1 + min_dist)][(int)(x1 - min_dist)] == DOORC
		|| data->map[(int)(y1 + min_dist)][(int)(x1 + min_dist)] == DOORC)
		return ;
	data->player->x_pos = x1;
	data->player->y_pos = y1;
	return ;
}

static void	mouse_movements(t_data *data)
{
	int	x;
	int	y;
	int	x1;
	int	y1;

	x1 = data->mlx->display_size_x / 2;
	y1 = data->mlx->display_size_y / 2;
	mlx_mouse_get_pos(data->mlx->mlx_ptr, data->mlx->win_ptr, &x, &y);
	if (x < x1 && data->keys[P] == -1)
	{
		data->player->rot_deg = fmod((data->player->rot_deg
					- data->player->rot_speed * 5 + PI * 2), PI * 2);
		mlx_mouse_move(data->mlx->mlx_ptr, data->mlx->win_ptr, x1, y1);
	}
	if (x > x1 && data->keys[P] == -1)
	{
		data->player->rot_deg = fmod((data->player->rot_deg
					+ data->player->rot_speed * 5), PI * 2);
		mlx_mouse_move(data->mlx->mlx_ptr, data->mlx->win_ptr, x1, y1);
	}
	if (data->keys[P] == -1)
		mlx_mouse_hide(data->mlx->mlx_ptr, data->mlx->win_ptr);
	else
		mlx_mouse_show(data->mlx->mlx_ptr, data->mlx->win_ptr);
	return ;
}

/**
 * @brief update player position and rotation values then render screen.
 * RAD = DEG * PI / 180
 * 
 * @param data 
 */
int	do_movements(t_data *data)
{
	if (data->keys[W] && data->keys[P] == -1)
		check_wall(data, (sin(data->player->rot_deg)
				* data->player->move_speed),
			-(cos(data->player->rot_deg) * data->player->move_speed));
	if (data->keys[A] && data->keys[P] == -1)
		check_wall(data, -(cos(data->player->rot_deg)
				* data->player->move_speed),
			-(sin(data->player->rot_deg) * data->player->move_speed));
	if (data->keys[S] && data->keys[P] == -1)
		check_wall(data, -(sin(data->player->rot_deg)
				* data->player->move_speed),
			(cos(data->player->rot_deg) * data->player->move_speed));
	if (data->keys[D] && data->keys[P] == -1)
		check_wall(data, (cos(data->player->rot_deg)
				* data->player->move_speed),
			(sin(data->player->rot_deg) * data->player->move_speed));
	if (data->keys[LEFT_ARROW] && data->keys[P] == -1)
		data->player->rot_deg = fmod((data->player->rot_deg
					- data->player->rot_speed + PI * 2), PI * 2);
	if (data->keys[RIGHT_ARROW] && data->keys[P] == -1)
		data->player->rot_deg = fmod((data->player->rot_deg
					+ data->player->rot_speed), PI * 2);
	mouse_movements(data);
	return (render(data), 1);
}
