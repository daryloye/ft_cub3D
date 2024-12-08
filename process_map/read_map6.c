/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 09:59:21 by wkoh              #+#    #+#             */
/*   Updated: 2024/12/08 10:00:03 by wkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_door_enclosed(t_data *data, int i, int j)
{
	if ((i > 0 && data->map[i - 1][j] != '1')
		|| (i < data->map_size_y - 1 && data->map[i + 1][j] != '1'))
	{
		if ((j > 0 && data->map[i][j - 1] != '1')
		|| ((size_t)j < ft_strlen(data->map[i]) - 1
		&& data->map[i][j + 1] != '1'))
			return (0);
		else
			return (1);
	}
	return (1);
}

int	check_door(t_data *data, int i)
{
	int	j;

	j = 0;
	while ((size_t)j < ft_strlen(data->map[i]))
	{
		if (data->map[i][j] == 'O' || data->map[i][j] == 'o')
		{
			if (!is_door_enclosed(data, i, j))
				return (-1);
		}
		j++;
	}
	return (0);
}
