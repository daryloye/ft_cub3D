/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:32:26 by daong             #+#    #+#             */
/*   Updated: 2024/10/27 12:18:53 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_data	*data;

	data = init_data();
	if (!data)
		return (clean_data("init_data", data), EXIT_FAILURE);
	mlx_loop(data->mlx->mlx_ptr);
	ft_printf("hello\n");
	return (clean_data(NULL, data), EXIT_SUCCESS);
}
