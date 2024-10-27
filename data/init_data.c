/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:05:57 by daong             #+#    #+#             */
/*   Updated: 2024/10/27 12:18:10 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Init data struct, which contains mlx struct
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
	init_hooks(data);
	return (data);
}

/**
 * @brief Clean data struct, which contains mlx struct
 * 
 * @param error_msg 
 * @param data 
 */
void	clean_data(char *error_msg, t_data *data)
{
	if (data->mlx)
		clean_mlx(data->mlx);
	if (data)
		free(data);
	if (error_msg)
		ft_printf("Error: %s\n", error_msg);
	return ;
}