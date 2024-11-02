/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:05:57 by daong             #+#    #+#             */
/*   Updated: 2024/11/03 01:22:03 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief init data struct
 * 
 * @return t_data*
 */
t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (NULL);
	data->mlx = init_mlx();
	if (!data->mlx)
		return (NULL);
	data->texture = init_texture();
	if (!data->texture)
		return (NULL);
	data->player = init_player();
	if (!data->player)
		return (NULL);
	data->map = ft_calloc(sizeof(char *), 1);
	if (!data->map)
		return (NULL);
	ft_memset(data->keys, 0, sizeof(data->keys));
	return (data);
}

/**
 * @brief clean data struct
 * 
 * @param data 
 */
void	clean_data(t_data *data)
{
	int	i;

	if (data->mlx)
		clean_mlx(data->mlx);
	if (data->texture)
		clean_texture(data->texture);
	if (data->player)
		clean_player(data->player);
	if (data->map)
	{
		i = -1;
		while (data->map[++i])
			free(data->map[i]);
		free(data->map);
	}
	if (data)
		free(data);
	return ;
}
