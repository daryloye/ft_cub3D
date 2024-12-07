/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:32:26 by daong             #+#    #+#             */
/*   Updated: 2024/12/07 10:14:22 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (print_error("Pls run program as './cub3D maps/map#.cub'"),
			EXIT_FAILURE);
	data = init_data();
	if (!data)
		return (print_error(strerror(errno)), clean_data(data), EXIT_FAILURE);
	if (read_file(av[1], data) == 1)
		return (clean_data(data), EXIT_FAILURE);
	if (data->map_size_x == 0 || data->map_size_y == 0)
		return (print_error("Invalid map size"), clean_data(data),
			EXIT_FAILURE);
	init_hooks(data);
	mlx_loop_hook(data->mlx->mlx_ptr, do_movements, data);
	mlx_loop(data->mlx->mlx_ptr);
	return (clean_data(data), EXIT_SUCCESS);
}
