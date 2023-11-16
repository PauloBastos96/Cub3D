# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 20:49:53 by paulorod          #+#    #+#              #
#    Updated: 2023/11/16 12:41:07 by paulorod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS =	src/main.c \
		src/cleaners.c \
		src/gameplay/player_controller.c \
		src/gameplay/player_movement_utils.c \
		src/parsing/parser.c \
		src/parsing/parsing_utils.c \
		src/parsing/map_parse_utils.c \
		src/parsing/player_parse_utils.c \
		src/rendering/mlx_initialization.c \
		src/rendering/render_utils.c \
		src/rendering/render_walls.c \
		src/rendering/rendering.c \
		src/rendering/time_utils.c \
		src/rendering/render_minimap.c \
		src/raycasting/raycaster.c \
		src/raycasting/raycasting_utils.c \
		src/math_utils.c \
		src/utils.c

MLX_PATH = ./minilibx-linux
MLX = $(MLX_PATH)/libmlx_Linux.a
LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a

OBJ :=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	echo "\033[0;36m[COMPILING CUB3D]\033[0m"
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT) $(MLX) -lX11 -lXext -lm
$(LIBFT):
	echo "\033[0;36m[COMPILING LIBFT]\033[0m"
	make -C $(LIBFT_PATH) bonus
$(MLX):
	echo "\033[0;36m[COMPILING MLX]\033[0m"
	make -C $(MLX_PATH) all

clean:
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean
	$(RM) $(OBJ)
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean
re: fclean all
