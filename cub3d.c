/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:32:26 by daong             #+#    #+#             */
/*   Updated: 2024/11/06 09:50:55 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* TEST MAP */
void	import_test_map(t_data *data)
{
	char	**map;

	map = ft_calloc(sizeof(char *), 6);
	map[0] = ft_strdup("11111");
	map[1] = ft_strdup("10001");
	map[2] = ft_strdup("10001");
	map[3] = ft_strdup("10001");
	map[4] = ft_strdup("11111");
	data->map = map;
}

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
		return (clean_data(data), EXIT_FAILURE);

	printf("---------- TEST MAP ----------\n");	
	import_test_map(data);
	for (int i = 0; data->map[i]; i++)
		printf("%s\n", data->map[i]);

	init_hooks(data);
	mlx_loop_hook(data->mlx->mlx_ptr, do_movements, data);
	mlx_loop(data->mlx->mlx_ptr);
	return (clean_data(data), EXIT_SUCCESS);
}
