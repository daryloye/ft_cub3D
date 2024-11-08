/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:30:52 by daong             #+#    #+#             */
/*   Updated: 2024/11/07 03:35:25 by daong            ###   ########.fr       */
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

# define WALL		1
# define FLOOR		0
# define DIRECTION	"NESW"

typedef enum
{
	W,
	A,
	S,
	D,
	LEFT_ARROW,
	RIGHT_ARROW,
	M,
	KEY_COUNT
}	key_index;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		display_size_x;
	int		display_size_y;
	void	*background_img;
	void	*minimap_wall_img;
	void	*minimap_floor_img;
	void	*minimap_player_img;
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
	double	move_speed;
	double	rot_deg;
	double	rot_speed;
	double	fov_deg;
}	t_player;

typedef struct s_data
{
	t_mlx		*mlx;
	t_texture	*texture;
	t_player	*player;
	char		**map;
	int			map_size_x;		// no. of columns
	int			map_size_y;		// no. of rows
	int			directions_found[4];
	int			keys[KEY_COUNT];
}	t_data;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

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
void		clean_images(t_mlx *mlx);

/* render/background */
int			render_background(t_data *data);

/* render/render_utils */
t_img		init_blank_image(t_data *data, int x, int y);
void		ft_mlx_pixel_put(t_img *img, int x, int y, int color);
int			create_trgb(int t, int r, int g, int b);
void		dda(t_data *data, float start[2], float end[2], int color);

/* minimap/minimap */
int			render_minimap(t_data *data);
void		clean_minimap(t_mlx *mlx);

/* minimap/minimap_background */
int			minimap_background(t_data *data, int wall_length);

/* minimap/minimap_player */
int			minimap_player(t_data *data, int wall_length);

/* process_map/read_file */
int			read_file(char *path, t_data *data);

/* process_map/read_texture */
int			get_textures(t_data *data, char **text);

/* process_map/read_color */
int			get_color(t_data *data, char **text);

/* process_map/read_map */
int			get_map(t_data *data, char **text);

/* process_map/read_identifier */
int			check_identifiers(char **text);

/* process_map/read_utils */
char		*skip_whitespaces(char *line);
void		remove_trailing_whitespace(char *line);
bool		is_empty_line(char *line);

/* movements */
int			do_movements(t_data *data);

#endif
