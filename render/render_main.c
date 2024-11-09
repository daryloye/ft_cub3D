/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:32:33 by daong             #+#    #+#             */
/*   Updated: 2024/11/09 17:45:35 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Cleans data and exits program if anything goes wrong in render
 * 
 * @param data 
 */
static void	render_error(t_data *data)
{
	ft_printf("Error\n%s\n", strerror(errno));
	clean_data(data);
	exit(EXIT_FAILURE);
}

/**
 * @brief Main render function. if error, calls render_error
 * 
 * @param data 
 */
void	render(t_data *data)
{
	if (render_background(data) == 1)
		render_error(data);
	if (data->keys[M] == 1)
		if (render_minimap(data) == 1)
			render_error(data);
	printf("x = %.2f, y = %.2f, rot_deg = %.2f\n",
		data->player->x_pos, data->player->y_pos, data->player->rot_deg);
	printf("int x = %d, int y = %d\n",
		(int)data->player->x_pos, (int)data->player->y_pos);
	return ;
}
