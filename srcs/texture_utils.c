/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:13:43 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/02 17:52:09 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		find_x(t_elts *e, t_text_data *text)
{
	int	res;

	if (e->ray.hit_wall_vert == 1)
		res = fmod(e->ray.wall_hit.y, 1) * text->width;
	else
		res = fmod(e->ray.wall_hit.x, 1) * text->width;
	return (res);
}

int		find_y(int y, t_elts *e, t_text_data *text)
{
	int	res;

	res = (y + e->ray.wall_height / 2 - e->win.y / 2) *
		(text->height / e->ray.wall_height);
	if (res < 0)
		res = 0;
	return (res);
}

int		find_color(int x, int y, t_text_data *text)
{
	char	*dst;
	int		texture_color;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > text->width)
		x = text->width;
	if (y > text->height)
		y = text->height;
	dst = text->addr + (y * text->size_line + x * (text->bpp / 8));
	texture_color = (*(unsigned int*)dst);
	return (texture_color);
}

int		check_open_file(char *name)
{
	int	fd;
	int	ret;

	ret = 1;
	fd = open(name, O_RDONLY);
	if (fd == -1)
		ret = 0;
	close(fd);
	return (ret);
}

int		check_open_texture(t_texture *text)
{
	if (check_open_file(text->north) == 0
		|| check_open_file(text->south) == 0
		|| check_open_file(text->east) == 0
		|| check_open_file(text->west) == 0
		|| check_open_file(text->sp) == 0)
		return (error_msg("Error\nOne of the textures is unknow.\n"));
	if (check_file(text->north, ".xpm") == 0
		|| check_file(text->south, ".xpm") == 0
		|| check_file(text->east, ".xpm") == 0
		|| check_file(text->west, ".xpm") == 0
		|| check_file(text->sp, ".xpm") == 0)
		return (error_msg("Error\nOne of the textures is not an .xpm file.\n"));
	return (1);
}
