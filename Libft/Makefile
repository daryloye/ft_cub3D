# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daong <daong@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 12:13:48 by daong             #+#    #+#              #
#    Updated: 2024/05/31 14:11:14 by daong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = ./ft_isalpha.c ./ft_isdigit.c ./ft_isalnum.c \
./ft_isascii.c ./ft_isprint.c ./ft_strlen.c \
./ft_memset.c ./ft_bzero.c ./ft_memcpy.c \
./ft_memmove.c ./ft_strlcpy.c ./ft_strlcat.c \
./ft_toupper.c ./ft_tolower.c ./ft_strchr.c \
./ft_strrchr.c ./ft_strncmp.c ./ft_memchr.c \
./ft_memcmp.c ./ft_strnstr.c ./ft_atoi.c \
./ft_calloc.c ./ft_strdup.c ./ft_substr.c \
./ft_strjoin.c ./ft_strtrim.c ./ft_split.c \
./ft_itoa.c ./ft_strmapi.c ./ft_striteri.c \
./ft_putchar_fd.c ./ft_putstr_fd.c ./ft_putendl_fd.c ./ft_putnbr_fd.c \
./ft_lstnew.c ./ft_lstadd_front.c ./ft_lstsize.c \
./ft_lstlast.c ./ft_lstadd_back.c ./ft_lstdelone.c \
./ft_lstclear.c ./ft_lstiter.c ./ft_lstmap.c \
./get_next_line.c	\
./ft_printf.c	\
./print_c.c 		./print_s.c		./print_p.c \
./print_id.c		./print_u.c		./print_x.c \
./print_percent.c	./ft_putnbr_base.c

OBJ_DIR = obj
OBJECTS = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

${NAME} : ${OBJECTS}
	ar -rc ${NAME} ${OBJECTS}

${OBJ_DIR}/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f ${OBJECTS}
	rmdir $(OBJ_DIR) 2>/dev/null || true

fclean : clean
	rm -f $(NAME)

re: fclean all
