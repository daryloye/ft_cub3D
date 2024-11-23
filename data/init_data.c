/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:05:57 by daong             #+#    #+#             */
/*   Updated: 2024/11/23 14:49:13 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief free map
 * 
 * @param data
 */
void	free_map(t_data *data)
{
	int	i;

	if (data->map == NULL)
		return ;
	i = 0;
	while (i < data->map_size_y)
	{
		if (data->map[i] != NULL)
			free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
}

/**
 * @brief free temp map
 * 
 * @param data
 */
void	free_temp_map(t_data *data)
{
	int	i;

	if (data->temp_map == NULL)
		return ;
	i = 0;
	while (i < data->map_size_y + 2)
	{
		if (data->temp_map[i] != NULL)
			free(data->temp_map[i]);
		i++;
	}
	free(data->temp_map);
	data->temp_map = NULL;
}

/**
 * @brief free visited map
 * 
 * @param data
 */
void	free_visited_map(t_data *data)
{
	int	i;

	if (data->visited_map == NULL)
		return ;
	i = 0;
	while (i < data->map_size_y + 2)
	{
		if (data->visited_map[i] != NULL)
			free(data->visited_map[i]);
		i++;
	}
	free(data->visited_map);
	data->visited_map = NULL;
}

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
	data->display = init_display(data);
	if (!data->display)
		return (NULL);
	data->minimap = init_minimap();
	if (!data->minimap)
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
	if (data->texture)
		clean_texture(data->texture);
	if (data->player)
		clean_player(data->player);
	if (data->display)
		clean_display(data->display, data->mlx);
	if (data->minimap)
		clean_minimap(data->minimap, data->mlx);
	if (data->map)
		free_map(data);
	if (data->temp_map)
		free_temp_map(data);
	if (data->visited_map)
		free_visited_map(data);
	if (data->mlx)
		clean_mlx(data->mlx);
	if (data)
		free(data);
	return ;
}
