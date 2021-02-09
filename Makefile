# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 11:22:00 by adupuy            #+#    #+#              #
#    Updated: 2021/02/09 15:13:34 by adupuy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = srcs/main.c \
		srcs/GNL/get_next_line.c \
		srcs/GNL/get_next_line_utils.c \
		srcs/Parsing/ft_parsing_elts.c \
		srcs/Parsing/ft_parsing_elts_utils.c \
		srcs/Parsing/ft_parsing_map.c \
		srcs/Parsing/check_error.c \
		srcs/Parsing/check_error_utils.c \
		srcs/Parsing/check_map.c \
		srcs/Parsing/utils.c \
		srcs/raycaster.c \
		srcs/draw.c \
		srcs/raycaster_utils.c \
		srcs/texture.c \
		srcs/texture_utils.c \
		srcs/sprite.c \
		srcs/sprite_utils.c \
		srcs/bmp.c \
		srcs/bmp_utils.c \
		srcs/utils.c \
		srcs/init.c \
		srcs/end_of_game.c \
		srcs/game.c \
		srcs/collision.c

OBJS = $(SRCS:.c=.o)

SRCS_BONUS = bonus/main.c \
			bonus/GNL/get_next_line.c \
			bonus/GNL/get_next_line_utils.c \
			bonus/Parsing/ft_parsing_elts.c \
			bonus/Parsing/ft_parsing_elts_utils.c \
			bonus/Parsing/ft_parsing_map.c \
			bonus/Parsing/check_error.c \
			bonus/Parsing/check_error_utils.c \
			bonus/Parsing/check_map.c \
			bonus/Parsing/utils.c \
			bonus/raycaster.c \
			bonus/draw.c \
			bonus/raycaster_utils.c \
			bonus/texture.c \
			bonus/texture_utils.c \
			bonus/sprite.c \
			bonus/sprite_utils.c \
			bonus/bmp.c \
			bonus/bmp_utils.c \
			bonus/utils.c \
			bonus/init.c \
			bonus/end_of_game.c \
			bonus/game.c \
			bonus/collision.c \
			bonus/draw_minimap.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

INCLD = -I Includes -I libft -I minilibx-linux

INCLD_BONUS = -I bonus/Includes -I libft -I minilibx-linux

CC = gcc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

LDFLAGS = -L libft -L minilibx-linux

LIBS = -lm -lft -lmlx -lXext -lX11

all: $(NAME)

$(NAME): $(OBJS)
	make -C minilibx-linux
	make bonus -C libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLD) -o $@ -c $<

bonus: $(OBJS_BONUS)
	make -C minilibx-linux
	make bonus -C libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS_BONUS) -o $(NAME) $(LIBS)

$(OBJS_BONUS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLD_BONUS) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
