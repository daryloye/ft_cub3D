# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daong <daong@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/27 09:24:53 by daong             #+#    #+#              #
#    Updated: 2024/10/27 09:24:53 by daong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC =	./cub3d.c	\
		./data/init_data.c		./data/init_mlx.c		./data/init_texture.c	\
		./data/init_player.c	./data/init_display.c	./data/init_minimap.c	\
		./input/hooks.c			./input/doors.c			./input/movements.c	\
		./render/render_main.c		./render/render_utils.c		./render/background.c	\
		./render/ray_direction.c	./render/ray_dir_utils.c	./render/ray_display.c	\
		./render/fps.c				./render/math_utils.c		./render/sprite.c	\
		./minimap/minimap.c			./minimap/minimap_background.c		./minimap/minimap_player.c	\
		./process_map/read_file.c		./process_map/read_texture.c	./process_map/read_texture2.c \
		./process_map/read_identifier.c	./process_map/read_utils.c	\
		./process_map/read_color.c		./process_map/read_color2.c		./process_map/read_map.c	\
		./process_map/read_map2.c		./process_map/read_map3.c	./process_map/read_map4.c \
		./process_map/read_map5.c	./process_map/read_map6.c	./process_map/read_map7.c \

OBJ_DIR = obj
OBJECTS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC)))

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11

MATH_FLAGS = -lm

all: $(LIBFT) $(MLX) $(NAME)

bonus: $(LIBFT) $(MLX) $(NAME_BONUS)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)

$(NAME_BONUS): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME_BONUS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(MLX):
	$(MAKE) -C $(MLX_DIR) all

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -I $(MLX_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

vpath %.c $(sort $(dir $(SRC)))

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rmdir $(OBJ_DIR) 2>/dev/null || true

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
