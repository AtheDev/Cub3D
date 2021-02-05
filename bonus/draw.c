/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:36:01 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/05 10:44:36 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_elts *e, int x, int y, int color)
{
	char	*pix;

	pix = e->img.addr + (y * e->img.size_line + x * (e->img.bpp / 8));
	*(int*)pix = color;
}

void	draw_line(int x, int start, t_elts *e, int color)
{
	double i;

	i = 0.0;
	if (start < 0)
		start = 0;
	if (e->ray.wall_height > e->win.y)
		e->ray.wall_height = e->win.y;
	while (i < e->ray.wall_height)
	{
		put_pixel(e, x, start, color);
		i += 1.0;
		start += 1;
	}
}

void	draw_rect(t_elts *e)
{
	int	i;
	int	j;
	int	color;

	i = -1;
	color = 0x000000;
	while (++i < (e->win.y))
	{
		j = -1;
		while (++j < (e->win.x))
			put_pixel(e, j, i, color);
	}
}
