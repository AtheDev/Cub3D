/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:28:56 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/07 20:26:26 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_delta(t_player *p)
{
	if (p->ray.y == 0)
		p->delta_dist.x = 0;
	else
	{
		if (p->ray.x == 0)
			p->delta_dist.x = 1;
		else
			p->delta_dist.x = abs(1 / p->ray.x);
	}
	if (p->ray.x == 0)
		p->delta_dist.y = 0;
	else
	{
		if (p->ray.y == 0)
			p->delta_dist.y = 1;
		else
			p->delta_dist.y = abs(1 / p->ray.y);
	}
}

void	find_side(t_player *p)
{
	if (p->ray.x < 0)
	{
		p->step.x = -1;
		p->side_dist.x = (p->pos.x - p->square_map.x) * p->delta_dist.x;
	}
	else
	{
		p->step.x = 1;
		p->side_dist.x = (p->square_map.x + 1.0 - p->pos.x) * p->delta_dist.x;
	}
	if (p->ray.y < 0)
	{
		p->step.y = -1;
		p->side_dist.y = (p->pos.y - p->square_map.y) * p->delta_dist.y;
	}
	else
	{
		p->step.y = 1;
		p->side_dist.y = (p->square_map.y + 1.0 - p->pos.y) * p->delta_dist.y;
	}
}

void	raytracing(t_elts *e)
{
	while (e->player.hit == 0)
	{
		if (e->player.side_dist.x < e->player.side_dist.y)
		{
			e->player.side_dist.x += e->player.delta_dist.x;
			e->player.square_map.x += e->player.step.x;
			e->player.side = 0;
		}
		else
		{
			e->player.side_dist.y += e->player.delta_dist.y;
			e->player.square_map.y += e->player.step.y;
			e->player.side = 1;
		}
		if(e->tab[e->player.square_map.x][e->player.square_map.y] > 0)
			e->player.hit = 1;
	}
}

void	before_drawing(t_player *p, t_win *win)
{
	if (p->side == 0)
		p->perp_wall_dist = (p->square_map.x - p->pos.x + (1 - p->step.x) / 2) / p->ray.x;
	else
		p->perp_wall_dist = (p->square_map.y - p->pos.y + (1 - p->step.y) / 2) / p->ray.y;
	p->line_h = (int)(win->x / p->perp_wall_dist);
	p->draw.x = -p->line_h / 2 + win->y / 2;
	if (p->draw.x < 0)
		p->draw.x = 0;
	p->draw.y = p->line_h / 2 + win->y / 2;
	if (p->draw.y >= win->y)
		p->draw.y = win->y - 1;
}

int	raycaster(t_elts *e)
{
	int	x;

	x = 0;
	while (x < e->win.x)
	{
		e->player.square_map.x = floor(e->player.pos.x);
		e->player.square_map.y = floor(e->player.pos.y);
		e->player.hit = 0;
		e->player.camera = 2 * x / (double)e->win.x - 1;
		e->player.ray.x = e->player.dir_pl.x + e->player.plane.x * e->player.camera;
		e->player.ray.y = e->player.dir_pl.y + e->player.plane.y * e->player.camera;
		find_delta(&e->player);
		find_side(&e->player);
		raytracing(e);
		before_drawing(&e->player, &e->win);
		vertical_line_draw(e, x);
		x++;
	}
	return (1);
}
