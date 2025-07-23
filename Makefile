# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 13:50:27 by fbraune           #+#    #+#              #
#    Updated: 2025/07/23 16:56:28 by fbraune          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src/
LIBFT_DIR = libft/
MLX42_DIR = mlx42/
MLX42_REPO = https://github.com/codam-coding-college/MLX42.git
INCLUDES = -I include/ -I $(LIBFT_DIR) -I $(MLX42_DIR)include/

SRC =	$(SRC_DIR)main.c \
		$(SRC_DIR)free_functions.c \
		$(SRC_DIR)allocate_functions.c \
		$(SRC_DIR)init_functions.c \
		$(SRC_DIR)small_utils_functions.c

OBJ = $(SRC:.c=.o)
LIBFT = $(LIBFT_DIR)libft.a
MLX42_LIB = $(MLX42_DIR)build/libmlx42.a

all: clone_mlx42 $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42_LIB) -o $(NAME) -lglfw -framework Cocoa -framework OpenGL -framework IOKit

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX42_LIB):
	cmake -B $(MLX42_DIR)build -S $(MLX42_DIR)
	cmake --build $(MLX42_DIR)build

clone_mlx42:
	@if [ ! -d "$(MLX42_DIR).git" ]; then \
		echo "Cloning MLX42 library..."; \
		git clone $(MLX42_REPO) $(MLX42_DIR); \
	else \
		echo "MLX42 already cloned."; \
	fi

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ) $(MLX42_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME) $(MLX42_DIR)

re: fclean all

.PHONY: all bonus clean fclean re clone_mlx42