/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:18:21 by daong             #+#    #+#             */
/*   Updated: 2024/12/07 09:57:18 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief init player struct
 * 
 * @return int t_player*
 */
t_player	*init_player(void)
{
	t_player	*player;

	player = ft_calloc(sizeof(t_player), 1);
	if (!player)
		return (NULL);
	player->mv_speed = 0.015;
	player->rot_speed = 0.015;
	player->fov_deg = 60 / 180.0 * PI;
	return (player);
}

/**
 * @brief clean player struct
 * 
 * @param player 
 */
void	clean_player(t_player *player)
{
	if (player)
		free(player);
	return ;
}
