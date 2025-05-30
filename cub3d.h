/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkoh <wkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:30:52 by daong             #+#    #+#             */
/*   Updated: 2024/12/09 17:04:53 by wkoh             ###   ########.fr       */
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
# include "sys/time.h"
# include "stdbool.h"

# define WALL			'1'
# define FLOOR			'0'
# define DOORO			'O'
# define DOORC			'o'
# define DIRECTION		"NESW"
# define PI 			3.14159265358979323846

typedef enum s_sprite_index
{
	SP_REST,
	SP_MOVE,
	SP_ROT_LEFT,
	SP_ROT_RIGHT,
	SP_PAUSE,
	SPRITE_COUNT
}	t_sprite_index;

typedef enum s_key_index
{
	W,
	A,
	S,
	D,
	LEFT_ARROW,
	RIGHT_ARROW,
	KEY_MAP,
	KEY_PAUSE,
	KEY_DOOR,
	KEY_SPRITE,
	KEY_COUNT
}	t_key_index;

typedef enum s_dir_index
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	DOOR_NS,
	DOOR_EW,
	DIR_COUNT
}	t_dir_index;

typedef enum s_ray_index
{
	START_X,
	START_Y,
	END_X,
	END_Y,
	NEW_X,
	NEW_Y,
	ANGLE,
	RAY_DIR,
	RAY_DIST,
	X_PIX,
	HEIGHT,
	POS_COUNT
}	t_ray_index;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

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
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
	t_img	door;
}	t_texture;

typedef struct s_player
{
	double	x_pos;
	double	y_pos;
	double	mv_speed;
	double	rot_deg;
	double	rot_speed;
	double	fov_deg;
}	t_player;

typedef struct s_display
{
	t_img	background;
	t_img	active;
	t_img	sprite[SPRITE_COUNT];
	double	sprite_inc;
}	t_display;

typedef struct s_minimap
{
	int		wall_length;
	int		player_length;
	int		display_scale;
	t_img	background;
	t_img	active;
}	t_minimap;

typedef struct s_data
{
	t_mlx		*mlx;
	t_texture	*texture;
	t_player	*player;
	t_display	*display;
	t_minimap	*minimap;
	char		**map;
	char		**temp_map;
	int			**visited_map;
	int			map_size_x;
	int			map_size_y;
	int			directions_found[4];
	int			keys[KEY_COUNT];
	int			fps;
	long long	start_time;
}	t_data;

/* data/init_data */
t_data		*init_data(void);
void		clean_data(t_data *data);
void		free_map(t_data *data);
void		free_temp_map(t_data *data);
void		free_visited_map(t_data *data);

/* data/init_mlx */
t_mlx		*init_mlx(void);
void		clean_mlx(t_mlx *mlx);

/* data/init_texture */
t_texture	*init_texture(void);
void		clean_texture(t_texture *texture, t_mlx *mlx);

/* data/init_player */
t_player	*init_player(void);
void		clean_player(t_player *player);

/* data/init_display */
t_display	*init_display(t_data *data);
void		clean_display(t_display *display, t_mlx *mlx);

/* data/init_minimap */
t_minimap	*init_minimap(void);
void		clean_minimap(t_minimap *minimap, t_mlx *mlx);

/* input/hooks */
void		init_hooks(t_data *data);

/* input/doors */
void		handle_doors(t_data *data);

/* input/movements */
int			do_movements(t_data *data);

/* render/render */
void		render(t_data *data);

/* render/background */
int			init_display_images(t_data *data);

/* render/ray_direction */
int			create_single_ray(t_data *data, double ray_angle, int x_pix);

/* render/ray_dir_utils */
int			check_in_map(t_data *data, double *ray);
int			check_in_map_mod(t_data *data, double *ray);
int			check_dist(double *ray, int dir, char map_c);

/* render/ray_display.c */
void		render_wall(t_data *data, double *ray);

/* render/render_utils */
t_img		init_blank_image(t_data *data, int x, int y);
void		ft_mlx_pixel_put(t_img img, int x, int y, int color);
int			trgb(int t, int r, int g, int b);
double		get_dist(double x1, double y1, double x2, double y2);

/* render/fps */
long long	current_time_ms(void);
void		wait_fps(t_data *data);

/* render/sprite */
void		render_sprite(t_data *data);
int			init_sprite(t_data *data, t_display *display);

/* render/math_utils.c */
int			ft_max(int x, int y);
int			ft_min(int x, int y);

/* minimap/minimap */
int			render_minimap(t_data *data);
void		dda_minimap(t_data *data, double *ray);

/* minimap/minimap_background */
int			minimap_background(t_data *data);

/* minimap/minimap_player */
int			minimap_player(t_data *data);

/* process_map/read_file */
int			read_file(char *path, t_data *data);

/* process_map/read_texture */
int			get_textures(t_data *data, char **text);

/* process_map/read_texture2 */
int			set_texture(void *mlx_ptr, char *file_path, t_img *texture);

/* process_map/read_color */
int			get_color(t_data *data, char **text);

/* process_map/read_color2 */
int			check_for_spaces(char *line);
int			parse_value(char *line, int *start);
int			parse_comma(char *line, int *start, int comma_count);
int			skip_initial_whitespace(char *line, int start);

/* process_map/read_map */
int			get_map(t_data *data, char **text);

/* process_map/read_map2 */
void		update_map_size(t_data *data);
void		sanitise_map(t_data *data);

/* process_map/read_map3 */
bool		is_map_enclosed(t_data *data);

/* process_map/read_map4 */
void		create_temp_map_with_border(t_data *data);
int			get_map_size(t_data *data, char **text, int i);
int			map_identifier(char *line);

/* process_map/read_map5 */
int			handle_empty_line(char *line, int line_index, int map_size_y);
int			check_map_line(char *line, int i, bool *player_found, t_data *data);

/* process_map/read_map6 */
int			check_door(t_data *data, int i);

/* process_map/read_map7 */
void		replace_whitespace_with_zero_mod(char **map, int map_size_y);
int			check_map(t_data *data);

/* process_map/read_identifier */
int			check_identifiers(char **text);

/* process_map/read_utils */
char		*skip_whitespaces(char *line);
void		remove_trailing_whitespace(char *line);
bool		is_empty_line(char *line);
void		print_error(char *str);

#endif
