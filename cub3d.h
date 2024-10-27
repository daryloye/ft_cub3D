/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:30:52 by daong             #+#    #+#             */
/*   Updated: 2024/10/27 19:23:49 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include "mlx.h"
# include "fcntl.h"
# include "stdio.h"
# include "errno.h"
# include "string.h"

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		display_size_x;
	int		display_size_y;
}	t_mlx;

typedef struct s_texture
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color;
	int		ceiling_color;
}	t_texture;

typedef struct s_data
{
	t_mlx		*mlx;
	t_texture	*texture;
	char		*map;
	int			horizon_height;
}	t_data;

/* data/init_data */
t_data		*init_data(void);
void		clean_data(t_data *data);

/* data/init_mlx */
t_mlx		*init_mlx(void);
void		clean_mlx(t_mlx *mlx);

/* data/init_texture */
t_texture	*init_texture(void);
void		clean_texture(t_texture *texture);

/* data/init_hooks */
void		init_hooks(t_data *data);

/* render/render */
void		render(t_data *data);

/* render/background */
void		render_background(t_data *data);

int			read_file(char *path, t_data *data);

#endif
