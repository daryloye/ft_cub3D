/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:32:26 by daong             #+#    #+#             */
/*   Updated: 2024/11/06 01:59:12 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (ft_printf("Error\nPls run program as './cub3D maps/map#.cub'\n"), EXIT_FAILURE);
	data = init_data();
	if (!data)
		return (ft_printf("Error\n%s\n", strerror(errno)),
			clean_data(data), EXIT_FAILURE);
	if (read_file(av[1], data) == 1)
		return (printf("QUITTING NOW"), clean_data(data), EXIT_FAILURE);
	init_hooks(data);
	mlx_loop_hook(data->mlx->mlx_ptr, do_movements, data);
	mlx_loop(data->mlx->mlx_ptr);
	return (clean_data(data), EXIT_SUCCESS);
}
