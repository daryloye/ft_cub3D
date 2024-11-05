/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <wkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:30:52 by daong             #+#    #+#             */
/*   Updated: 2024/11/04 20:05:16 by wkoh             ###   ########.fr       */
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
# include "math.h"
# include "stdbool.h"

typedef enum
{
	W,
	A,
	S,
	D,
	LEFT_ARROW,
	RIGHT_ARROW,
	KEY_COUNT
}	key_index;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		display_size_x;
	int		display_size_y;
	int		horizon_height;
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

typedef struct s_player
{
	double	x;
	double	y;
	double	rot_deg;
	double	fov_deg;
}	t_player;

typedef struct s_data
{
	t_mlx		*mlx;
	t_texture	*texture;
	t_player	*player;
	char		**map;
	int			keys[KEY_COUNT];
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

/* data/init_player */
t_player	*init_player(void);
void		clean_player(t_player *player);

/* data/init_hooks */
void		init_hooks(t_data *data);

/* render/render */
void		render(t_data *data);

/* render/background */
int			render_background(t_data *data);

/* render/minimap */
int			render_minimap(t_data *data);

/* process_map/read_file */
int			read_file(char *path, t_data *data);

/* process_map/read_texture */
int			get_textures(t_data *data, char **text);

/* process_map/read_identifier */
int			check_identifiers(char **text);

/* process_map/read_utils */
char	*skip_whitespaces(char *line);

/* movements */
int		do_movements(t_data *data);

#endif
