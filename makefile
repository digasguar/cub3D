# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/16 22:04:50 by dgasco-g          #+#    #+#              #
#    Updated: 2025/11/25 12:42:49 by dgasco-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRC_DIR	= src/
LIBFT_DIR = libft/
MLX_DIR = minilibx-linux/
INC_DIR = includes/
SRC_BONUS = bonus/

SRC_FILES = cub3D.c \
			player.c \
			load_textures.c \
			render.c \
			hooks.c \
			game_loop.c \
			parse_ids.c \
			parse_map.c \
			parse_utils.c \
			parse_utils2.c \
			valid_args.c \
			render_aux.c \
			render_aux2.c \
			exit_and_errors.c \
			parse_ids2.c \
			utils.c

BONUS_FILES = cub3D.c \
			player.c \
			load_textures.c \
			render.c \
			hooks.c \
			game_loop.c \
			parse_ids.c \
			parse_map.c \
			parse_utils.c \
			parse_utils2.c \
			valid_args.c \
			exit_and_errors.c \
			mini_map.c \
			render_aux.c \
			render_aux2.c \
			parse_ids2.c \
			utils.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

BONUS = $(addprefix $(SRC_BONUS), $(BONUS_FILES))

OBJS = $(SRC:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

LIBFT = $(LIBFT_DIR)libft.a
MINILIBX = $(MLX_DIR)libmlx.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS = -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MLX_DIR)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re:	fclean all

bonus: $(LIBFT) $(MINILIBX) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) $(MINILIBX) $(LDFLAGS) -o $(NAME)

$(SRC_BONUS)%.o: $(SRC_BONUS)%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus