/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 10:59:35 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/18 17:30:30 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_render(t_elts *e)
{
	double	size;
	double	x;
	double	y;
	double	i;
	int		r;

	r = -1;
	size = SIZE * MINI;
	while (++r < 360)
	{
		i = 0.0;
		while (i < 3.0 * MINI)
		{
			x = (e->player.pos.x * size) + cos(r) * i;
			y = (e->player.pos.y * size) + sin(r) * i;
			put_pixel(e, x, y, 0xFF0000);
		//	mlx_pixel_put(e->win.mlx_ptr, e->win.win_ptr, x, y, 0xFF0000);
			i += 1.0;
		}
	}
}

void	map_render(t_elts *e)
{
	double size;
	int	i;
	int	j;
	int	x;
	int	y;

	size = SIZE * MINI;
	j = -1;
	while (++j < e->width)
	{
		i = -1;
		while (++i < e->height)
			if (e->tab[i][j] > 0)
			{
				y = 0 + (j * size) - 1;
				while (++y < size + (j * size))
				{
					x = 0 + (i * size) - 1;
					while (++x < size + (i * size))
					{
						if (e->tab[i][j] == 1)
							put_pixel(e, y, x, 0xFFFFFF);
						//	mlx_pixel_put(e->win.mlx_ptr, e->win.win_ptr, y, x, 0xFFFFFF);
						else
							put_pixel(e, y, x, 0x00FF00);
						//	mlx_pixel_put(e->win.mlx_ptr, e->win.win_ptr, y, x, 0x00FF00);
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
	double	size;

	size = SIZE * MINI;
	i = 0.0;
	while (i < (e->ray.dist * MINI))
	{
		x = (e->player.pos.x * size) + cos(e->ray.angle) * i;
		y = (e->player.pos.y * size) + sin(e->ray.angle) * i;
		put_pixel(e, x, y, 0x0000FF);
	//	mlx_pixel_put(e->win.mlx_ptr, e->win.win_ptr, x, y, 0x0000FF);
		i += 1.0;
	}
}
