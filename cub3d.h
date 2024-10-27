/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:30:52 by daong             #+#    #+#             */
/*   Updated: 2024/10/27 12:18:31 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "Libft/libft.h"
# include "mlx.h"
# include "fcntl.h"
# include "stdio.h"

# define DISPLAY_X 1920
# define DISPLAY_Y 1080

typedef struct s_mlx {
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct s_data {
	t_mlx	*mlx;
}	t_data;

/* data */
t_data	*init_data(void);
void	clean_data(char *error_msg, t_data *data);

t_mlx	*init_mlx(void);
void	clean_mlx(t_mlx *mlx);

void	init_hooks(t_data *data);


#endif
