/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <wkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 09:24:01 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/08 13:09:01 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_map_size(t_data *data)
{
	int	new_size_x;
	int	y;

	new_size_x = 0;
	y = -1;
	while (data->map[++y])
		new_size_x = ft_max(ft_strlen(data->map[y]), new_size_x);
	data->map_size_x = new_size_x;
	return ;
}

void	sanitise_map(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '\n')
				data->map[y][x] = '\0';
		}
	}
	return ;
}