# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 11:22:00 by adupuy            #+#    #+#              #
#    Updated: 2021/02/02 10:56:52 by adupuy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = main.c GNL/get_next_line.c GNL/get_next_line_utils.c Parsing/ft_parsing_elts.c \
	Parsing/ft_parsing_elts_utils.c Parsing/ft_parsing_map.c Parsing/check_error.c \
	Parsing/check_map.c Parsing/utils.c raycaster.c draw.c raycaster_utils.c \
	draw_minimap.c texture.c texture_utils.c sprite.c sprite_utils.c bmp.c \
	bmp_utils.c utils.c init.c end_of_game.c game.c

OBJS = $(SRCS:.c=.o)

INCLD = -I Includes -I libft -I minilibx-linux

CC = gcc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

LDFLAGS = -L libft -L minilibx-linux

LIBS = -lm -lft -lmlx -lXext -lX11


all: $(NAME)

$(NAME): $(OBJS)
	make -C minilibx-linux
	make bonus -C libft
	$(CC) $(CFLAGS) ${LDFLAGS} $(OBJS) -o $(NAME) $(LIBS)

$(OBJS): %.o: %.c
	$(CC) ${CFLAGS} $(INCLD) -o $@ -c $<

clean::

	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
