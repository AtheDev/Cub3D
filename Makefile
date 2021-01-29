# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 11:22:00 by adupuy            #+#    #+#              #
#    Updated: 2021/01/29 10:15:38 by adupuy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = main.c GNL/get_next_line.c GNL/get_next_line_utils.c Parsing/ft_parsing_elts.c \
	Parsing/ft_parsing_elts_utils.c Parsing/ft_parsing_map.c Parsing/check_error.c \
	Parsing/check_map.c Parsing/utils.c raycaster.c draw2.c raycaster_utils.c \
	draw_minimap.c texture.c texture_utils.c sprite.c sprite_utils.c bmp.c \
	bmp_utils.c

OBJS = $(SRCS:.c=.o)

INCLD = Includes

CC = gcc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

LIB = Library

lft = libft

LIBS = -L $(LIB)/minilibx-linux/ -lm -lmlx -lXext -lX11


all: $(NAME)

$(NAME): $(OBJS)
	make -C Library/minilibx-linux
	make bonus -C $(lft)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(lft) -lft $(LIBS)

$(OBJS): %.o: %.c
	$(CC) -I $(INCLD) -o $@ -c $<

clean::

	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
