/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:32:36 by daong             #+#    #+#             */
/*   Updated: 2024/11/25 00:53:06 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief get current time in milliseconds
 * 
 * @return long 
 */
long long	current_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @brief waits until it is time for the next frame
 * 
 * @param data 
 * @return true 
 * @return false 
 */
void	wait_fps(t_data *data)
{
	long long	frame_ms;

	frame_ms = 1000 / data->fps;
	while (1)
	{
		if ((current_time_ms() - data->start_time) % frame_ms == 0)
			break;
	}
	return ;
}
