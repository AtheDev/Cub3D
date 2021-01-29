/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:13:43 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/29 16:41:36 by adupuy           ###   ########.fr       */
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

void	init_text_ptr(t_elts *e)
{
	e->text_data_n.text_ptr = NULL;
	e->text_data_s.text_ptr = NULL;
	e->text_data_w.text_ptr = NULL;
	e->text_data_e.text_ptr = NULL;
	e->text_sprite.text_ptr = NULL;
	e->tab_sp = NULL;
}
