/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 13:01:16 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/02 10:51:05 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_side_horz(t_elts *e, int u)
{
	e->ray.side_dist.y = floor(e->player.pos.y);
	e->ray.side_dist.y += (e->ray.down == 1) ? 1 : 0;
	e->ray.side_dist.x = e->player.pos.x +
		(e->ray.side_dist.y - e->player.pos.y) / tan(e->ray.angle);
	e->ray.step.y = (e->ray.up == 0) ? 1 : -1;
	e->ray.step.x = 1 / tan(e->ray.angle);
	e->ray.step.x *= ((e->ray.left == 1 && e->ray.step.x > 0) ||
		(e->ray.right == 1 && e->ray.step.x < 0)) ? -1 : 1;
	e->ray.touch.x = e->ray.side_dist.x;
	e->ray.touch.y = e->ray.side_dist.y;
	while (e->ray.touch.x >= 0 && e->ray.touch.x <= e->win.x &&
		e->ray.touch.y >= 0 && e->ray.touch.y <= e->win.y)
	{
		u = (e->ray.up == 1) ? 1 : 0;
		if (is_wall(e->ray.touch.x, e->ray.touch.y - u, e) == 1)
		{
			e->ray.found_horz_wall_hit = 1;
			e->ray.horz_wall_hit.x = e->ray.touch.x;
			e->ray.horz_wall_hit.y = e->ray.touch.y;
			break ;
		}
		e->ray.touch.x += e->ray.step.x;
		e->ray.touch.y += e->ray.step.y;
	}
}

void	find_side_vert(t_elts *e, int u)
{
	e->ray.side_dist.x = floor(e->player.pos.x);
	e->ray.side_dist.x += (e->ray.right == 1) ? 1 : 0;
	e->ray.side_dist.y = e->player.pos.y +
		(e->ray.side_dist.x - e->player.pos.x) * tan(e->ray.angle);
	e->ray.step.x = (e->ray.left == 0) ? 1 : -1;
	e->ray.step.y = tan(e->ray.angle);
	e->ray.step.y *= ((e->ray.up == 1 && e->ray.step.y > 0) ||
		(e->ray.down == 1 && e->ray.step.y < 0)) ? -1 : 1;
	e->ray.touch.x = e->ray.side_dist.x;
	e->ray.touch.y = e->ray.side_dist.y;
	while (e->ray.touch.x >= 0 && e->ray.touch.x <= e->win.x &&
		e->ray.touch.y >= 0 && e->ray.touch.y <= e->win.y)
	{
		u = (e->ray.left == 1) ? 1 : 0;
		if (is_wall(e->ray.touch.x - u, e->ray.touch.y, e) == 1)
		{
			e->ray.found_vert_wall_hit = 1;
			e->ray.vert_wall_hit.x = e->ray.touch.x;
			e->ray.vert_wall_hit.y = e->ray.touch.y;
			break ;
		}
		e->ray.touch.x += e->ray.step.x;
		e->ray.touch.y += e->ray.step.y;
	}
}

void	compare_dist(t_elts *e)
{
	double	horz_hit_dist;
	double	vert_hit_dist;

	horz_hit_dist = (e->ray.found_horz_wall_hit == 1) ?
		dist_between_two_points(e->ray.horz_wall_hit.x,
		e->player.pos.x, e->ray.horz_wall_hit.y,
		e->player.pos.y) : INT_MAX;
	vert_hit_dist = (e->ray.found_vert_wall_hit == 1) ?
		dist_between_two_points(e->ray.vert_wall_hit.x,
		e->player.pos.x, e->ray.vert_wall_hit.y,
		e->player.pos.y) : INT_MAX;
	if (horz_hit_dist < vert_hit_dist)
	{
		e->ray.wall_hit.x = e->ray.horz_wall_hit.x;
		e->ray.wall_hit.y = e->ray.horz_wall_hit.y;
		e->ray.dist = horz_hit_dist;
	}
	else
	{
		e->ray.wall_hit.x = e->ray.vert_wall_hit.x;
		e->ray.wall_hit.y = e->ray.vert_wall_hit.y;
		e->ray.dist = vert_hit_dist;
		e->ray.hit_wall_vert = 1;
	}
}

void	ray_cast(t_elts *e, int x)
{
	find_side_horz(e, 0);
	find_side_vert(e, 0);
	compare_dist(e);
	e->ray.dist_correct = e->ray.dist *
		cos(e->ray.angle - e->player.rotate_radius);
	e->ray.dist_project = (e->win.x / 2) / tan(e->player.fov / 2);
	e->ray.wall_height = e->ray.dist_project / e->ray.dist_correct;
	e->ray.top_pixel = (e->win.y / 2) - (e->ray.wall_height / 2);
	e->ray.bottom_pixel = (e->win.y / 2) + (e->ray.wall_height / 2);
	choose_texture(e, x);
	e->ray.wall_height = e->ray.top_pixel;
	draw_line(x, 0, e, e->color.c_color);
	e->ray.wall_height = e->win.y - e->ray.bottom_pixel;
	draw_line(x, e->ray.bottom_pixel, e, e->color.f_color);
}

void	cast_all_rays(t_elts *e, double *buf)
{
	int x;

	x = -1;
	e->ray.angle = e->player.rotate_radius - (e->player.fov / 2);
	while (++x < e->win.x)
	{
		init_ray(&e->ray);
		ray_cast(e, x);
		buf[x] = e->ray.dist;
		e->ray.angle += e->player.fov / e->win.x;
	}
}
