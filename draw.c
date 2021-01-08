/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:36:01 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/07 20:14:52 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vertical_line_draw(t_elts *e, int x)
{
	int	y;
	int	color;

	if (e->tab[e->player.square_map.x][e->player.square_map.y] == 1)
		color = 0xFF0000;
	else if (e->tab[e->player.square_map.x][e->player.square_map.y] == 2)
		color = 0x00FF00;
	//	if (elts->player.side == 1)
	//		color = color / 2;

	y = e->player.draw.x;
	while (y < e->player.draw.y)
	{
		mlx_pixel_put(e->win.mlx_ptr, e->win.win_ptr, x, y, color);
		y++;
	}
	y = 0;
	while (y < e->player.draw.x)
	{
		mlx_pixel_put(e->win.mlx_ptr, e->win.win_ptr, x, y, 0x0000FF);
		y++;
	}
}
