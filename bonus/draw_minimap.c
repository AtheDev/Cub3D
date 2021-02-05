/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 10:59:35 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/05 10:44:25 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_render(t_elts *e)
{
	double	x;
	double	y;
	double	i;
	int		r;

	r = -1;
	while (++r < 360)
	{
		i = 0.0;
		while (i < 3.0)
		{
			x = (e->player.pos.x * e->minimap.size) + cos(r) * i;
			y = (e->player.pos.y * e->minimap.size) + sin(r) * i;
			put_pixel(e, x, y, 0xFF0000);
			i += 1.0;
		}
	}
}

void	map_render(t_elts *e, int i, int j)
{
	int		x;
	int		y;

	while (++j < e->width)
	{
		i = -1;
		while (++i < e->height)
			if (e->tab[i][j] >= 0)
			{
				y = 0 + (j * e->minimap.size) - 1;
				while (++y < e->minimap.size + (j * e->minimap.size))
				{
					x = 0 + (i * e->minimap.size) - 1;
					while (++x < e->minimap.size + (i * e->minimap.size))
					{
						if (e->tab[i][j] == 1)
							put_pixel(e, y, x, 0xFFFFFF);
						else
							put_pixel(e, y, x, 0x7F6000);
					}
				}
			}
	}
}

void	ray_render(t_elts *e)
{
	double	i;
	double	x;
	double	y;

	i = 0.0;
	while (i < (e->ray.dist) * e->minimap.size)
	{
		x = (e->player.pos.x * e->minimap.size) + cos(e->ray.angle) * i;
		y = (e->player.pos.y * e->minimap.size) + sin(e->ray.angle) * i;
		put_pixel(e, x, y, 0x0000FF);
		i += 1.0;
	}
}

void	sprite_render(t_elts *e, int j)
{
	double	x;
	double	y;
	double	i;
	int		r;

	while (++j < e->num_sp)
	{
		r = -1;
		while (++r < 360)
		{
			i = 0.0;
			while (i < 3.0)
			{
				x = (e->tab_sp[j].pos.x * e->minimap.size) + cos(r) * i;
				y = (e->tab_sp[j].pos.y * e->minimap.size) + sin(r) * i;
				if (e->tab_sp[j].num == 2)
					put_pixel(e, x, y, 0x336633);
				if (e->tab_sp[j].num == 3)
					put_pixel(e, x, y, 0xFF6633);
				i += 1.0;
			}
		}
	}
}

int		display_minimap(t_elts *e)
{
	e->minimap.size_w = e->win.x / e->width;
	e->minimap.size_h = e->win.y / e->height;
	e->minimap.size = e->minimap.size_w > e->minimap.size_h ?
		e->minimap.size_h : e->minimap.size_w;
	draw_rect(e);
	map_render(e, -1, -1);
	cast_all_rays(e, (void *)0);
	player_render(e);
	sprite_render(e, -1);
	return (1);
}
