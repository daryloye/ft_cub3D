/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:32:26 by daong             #+#    #+#             */
/*   Updated: 2024/11/27 16:25:51 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	test_map(t_data *data)
// {
// 	if (data->map)
// 	{
// 		for (int i = 0; data->map[i]; i++)
// 			free(data->map[i]);
// 		free(data->map);
// 	}
// 	char **map;
// 	map = ft_calloc(sizeof (char *), 6);
// 	if (!map)
// 		exit(1);
// 	map[0] = ft_strdup("11111");
// 	map[1] = ft_strdup("10101");
// 	map[2] = ft_strdup("10001");
// 	map[3] = ft_strdup("10001");
// 	map[4] = ft_strdup("11111");
// 	data->map = map;
// 	data->map_size_x = 5;
// 	data->map_size_y = 5;
// 	data->player->rot_deg = 0;
// 	data->player->x_pos = 3;
// 	data->player->y_pos = 3;
// 	data->texture->ceiling_color = create_trgb(0, 125, 125, 0);
// 	data->texture->floor_color = create_trgb(0, 125, 0, 125);

// 	data->texture->north.img_ptr = mlx_xpm_file_to_image(data->mlx->mlx_ptr, "img/wall_north.xpm", &(data->texture->img_pix), &(data->texture->img_pix));
// 	data->texture->north.addr = mlx_get_data_addr(data->texture->north.img_ptr, &(data->texture->north.bits_per_pixel), &(data->texture->north.line_length), &(data->texture->north.endian));
	
// 	data->texture->south.img_ptr = mlx_xpm_file_to_image(data->mlx->mlx_ptr, "img/wall_south.xpm", &(data->texture->img_pix), &(data->texture->img_pix));
// 	data->texture->south.addr = mlx_get_data_addr(data->texture->south.img_ptr, &(data->texture->south.bits_per_pixel), &(data->texture->south.line_length), &(data->texture->south.endian));
	
// 	data->texture->east.img_ptr = mlx_xpm_file_to_image(data->mlx->mlx_ptr, "img/wall_east.xpm", &(data->texture->img_pix), &(data->texture->img_pix));
// 	data->texture->east.addr = mlx_get_data_addr(data->texture->east.img_ptr, &(data->texture->east.bits_per_pixel), &(data->texture->east.line_length), &(data->texture->east.endian));
	
// 	data->texture->west.img_ptr = mlx_xpm_file_to_image(data->mlx->mlx_ptr, "img/wall_west.xpm", &(data->texture->img_pix), &(data->texture->img_pix));
// 	data->texture->west.addr = mlx_get_data_addr(data->texture->west.img_ptr, &(data->texture->west.bits_per_pixel), &(data->texture->west.line_length), &(data->texture->west.endian));
// }

void	print_error(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return ;
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (print_error("Pls run program as './cub3D maps/map#.cub'"), EXIT_FAILURE);
	data = init_data();
	if (!data)
		return (print_error(strerror(errno)), clean_data(data), EXIT_FAILURE);
	if (read_file(av[1], data) == 1)
		return (clean_data(data), EXIT_FAILURE);
	
	// if (av[1] == NULL)
	// 	return (0);
	// test_map(data);
	// for (int i = 0; data->map[i]; i++)
	// 	printf("%s\n", data->map[i]);

	init_hooks(data);
	mlx_loop_hook(data->mlx->mlx_ptr, do_movements, data);
	mlx_loop(data->mlx->mlx_ptr);
	return (clean_data(data), EXIT_SUCCESS);
}
