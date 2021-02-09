/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:17:06 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/09 14:21:36 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize_window(t_win *win)
{
	int	width_screen;
	int	height_screen;

	mlx_get_screen_size(win->mlx_ptr, &width_screen, &height_screen);
	if (width_screen < win->x)
		win->x = width_screen;
	if (height_screen < win->y)
		win->y = height_screen;
}

int		init_window(t_win *win)
{
	win->mlx_ptr = mlx_init();
	if (win->mlx_ptr == NULL)
		return (0);
	return (1);
}

int		init_win(t_win *win, int save)
{
	if (save == 0)
	{
		resize_window(win);
		win->win_ptr = mlx_new_window(win->mlx_ptr, win->x, win->y, "cub3D");
		if (win->win_ptr == NULL)
			return (0);
	}
	else
	{
		if (win->x * win->y > 1000000000 || win->x * win->y <= 0)
			return (msg2(6));
		win->win_ptr = NULL;
	}
	return (1);
}

int		init_image(t_elts *e)
{
	e->img.img_ptr = mlx_new_image(e->win.mlx_ptr, e->win.x, e->win.y);
	if (e->img.img_ptr == NULL)
		return (0);
	e->img.addr = mlx_get_data_addr(e->img.img_ptr, &(e->img.bpp),
				&(e->img.size_line), &(e->img.endian));
	return (1);
}

void	init_player(t_elts *e)
{
	e->player.turn_direct = 0;
	e->player.walk_direct = 0;
	e->player.walk_sideways = 0;
	if (e->player.dir == 30)
		e->player.rotate_radius = 3 * M_PI_2;
	else if (e->player.dir == 21)
		e->player.rotate_radius = 0;
	else if (e->player.dir == 35)
		e->player.rotate_radius = M_PI_2;
	else if (e->player.dir == 39)
		e->player.rotate_radius = M_PI;
	e->player.move_speed = 0.1;
	e->player.rotate_speed = 2 * (M_PI / 180);
	e->minimap.display = 0;
}
