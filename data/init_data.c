/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:05:57 by daong             #+#    #+#             */
/*   Updated: 2024/10/27 18:50:13 by daong            ###   ########.fr       */
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
	data->map = ft_strdup("");
	if (!data->map)
		return (NULL);
	data->horizon_height = data->mlx->display_size_y / 2;
	init_hooks(data);
	return (data);
}

/**
 * @brief clean data struct
 * 
 * @param data 
 */
void	clean_data(t_data *data)
{
	if (data->mlx)
		clean_mlx(data->mlx);
	if (data->texture)
		clean_texture(data->texture);
	if (data->map)
		free(data->map);
	if (data)
		free(data);
	return ;
}
