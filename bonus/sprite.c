/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:38:01 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/05 10:58:03 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_sprite(t_elts *e)
{
	e->num_sp = count_sprite(e);
	e->tab_sp = malloc(sizeof(t_sprite) * e->num_sp);
	if (e->tab_sp == NULL)
		return (0);
	complete_tab_sprite(e);
	return (1);
}

void	draw_sprite_texture_next(t_sprite *sp, t_elts *e, int tot_x, int y)
{
	int	transp;
	int	color;

	if (sp->num == 2)
	{
		transp = find_color(0, 32, &e->text_sprite);
		color = find_color(sp->text_offset.x,
			sp->text_offset.y, &e->text_sprite);
	}
	if (sp->num == 3)
	{
		transp = find_color(0, 32, &e->text_sprite2);
		color = find_color(sp->text_offset.x,
			sp->text_offset.y, &e->text_sprite2);
	}
	if (color != transp)
		put_pixel(e, tot_x, y, color);
}

void	draw_sprite_texture(t_sprite *sp, t_elts *e, int x, int first_x)
{
	int	y;
	int	res;

	sp->text_offset.x = x * e->text_sprite.width / sp->height_sprite;
	y = sp->top_pixel - 1;
	while (++y < sp->bottom_pixel)
	{
		res = ((y + sp->height_sprite / 2.0) - (e->win.y / 2.0)) *
			((double)e->text_sprite.height / (double)sp->height_sprite);
		if (res < 0)
			res = 0;
		sp->text_offset.y = res;
		draw_sprite_texture_next(sp, e, x + first_x, y);
	}
}

void	sp_is_visible(t_elts *e, t_sprite *sp, double *buff)
{
	double	dist_project;
	double	x0;
	double	first_x;
	int		x;
	int		x1;

	dist_project = (e->win.x / 2) / tan(e->player.fov / 2);
	sp->height_sprite = dist_project / sp->dist;
	sp->top_pixel = (e->win.y / 2) - (sp->height_sprite / 2);
	if (sp->top_pixel < 0)
		sp->top_pixel = 0;
	sp->bottom_pixel = (e->win.y / 2) + (sp->height_sprite / 2);
	if (sp->bottom_pixel > e->win.y)
		sp->bottom_pixel = e->win.y;
	x0 = tan(sp->angle) * dist_project;
	first_x = (e->win.x / 2) + x0 - (sp->height_sprite / 2);
	x = -1;
	while (first_x + x < 0)
		x++;
	while (++x < sp->height_sprite && (first_x + x) < e->win.x)
	{
		x1 = (int)(first_x + x);
		if (buff[x1] > sp->dist)
			draw_sprite_texture(sp, e, x, first_x);
	}
}

void	render_sprites(double *buff, t_elts *e)
{
	int	i;

	i = -1;
	find_dist(e);
	sort_sprites(e);
	find_angle(e, -1);
	while (++i < e->num_sp)
		if (e->tab_sp[i].visible == 1)
			sp_is_visible(e, &e->tab_sp[i], buff);
}
