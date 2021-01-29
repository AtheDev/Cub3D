/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:28:12 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/29 16:03:50 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		count_sprite(t_elts *e)
{
	int	count;
	int	w;
	int	h;

	count = 0;
	h = -1;
	while (++h < e->height)
	{
		w = -1;
		while (++w < e->width)
		{
			if (e->tab[h][w] == 2)
				count++;
		}
	}
	return (count);
}

void	complete_tab_sprite(t_elts *e)
{
	int	w;
	int	h;
	int	num;

	h = -1;
	num = 0;
	while (++h < e->height)
	{
		w = -1;
		while (++w < e->width)
			if (e->tab[h][w] == 2)
			{
				e->tab_sp[num].pos.x = w + 0.5;
				e->tab_sp[num].pos.y = h + 0.5;
				e->tab_sp[num].dist = 0.0;
				e->tab_sp[num].angle = 0.0;
				e->tab_sp[num].visible = 0;
				num++;
			}
	}
}

void	find_dist(t_elts *e)
{
	int	i;

	i = -1;
	while (++i < e->num_sp)
	{
		e->tab_sp[i].dist = dist_between_two_points(e->player.pos.x,
		e->tab_sp[i].pos.x, e->player.pos.y, e->tab_sp[i].pos.y);
	}
}

void	sort_sprites(t_elts *e)
{
	t_sprite	tmp;
	int			i;

	i = 0;
	while (i < e->num_sp - 1)
	{
		if (e->tab_sp[i].dist < e->tab_sp[i + 1].dist)
		{
			tmp = e->tab_sp[i];
			e->tab_sp[i] = e->tab_sp[i + 1];
			e->tab_sp[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	find_angle(t_elts *e, int i)
{
	double	dist_x;
	double	dist_y;
	double	angle_player_sp;
	double	diff_angle;

	while (++i < e->num_sp)
	{
		dist_x = e->tab_sp[i].pos.x - e->player.pos.x;
		dist_y = e->tab_sp[i].pos.y - e->player.pos.y;
		angle_player_sp = atan2(dist_y, dist_x);
		e->tab_sp[i].angle = angle_player_sp - e->player.rotate_radius;
		e->tab_sp[i].angle = normalize_angle(e->tab_sp[i].angle);
		if (e->tab_sp[i].angle < -M_PI)
			e->tab_sp[i].angle += 2.0 * M_PI;
		if (e->tab_sp[i].angle > M_PI)
			e->tab_sp[i].angle -= 2.0 * M_PI;
		if (abs(e->tab_sp[i].angle) < (e->player.fov / 2))
			e->tab_sp[i].visible = 1;
		else
			e->tab_sp[i].visible = 0;
	}
}
