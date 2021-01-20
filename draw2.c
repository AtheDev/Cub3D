/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 19:36:01 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/20 14:55:46 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keyPress(int key, t_elts *e)
{
	if (key == Z || key == D || key == W || key == FORWARD)
		e->player.walk_direct = 1;
	else if (key == S || key == Q || key == A || key == BACK)
		e->player.walk_direct = -1;
	if (key == Q || key == D || key == A)
		e->player.walk_sideways = 1;
	if (key == RIGHT)
		e->player.turn_direct = 1;
	else if (key == LEFT)
		e->player.turn_direct = -1;
	if (key == ESC)
		keyExit(e);	
printf("key = %c et %d\n", key, key);
	return (1);
}

int	keyRelease(int key, t_elts *e)
{
	if (key == Z || key == D || key == S || key == Q || key == W || key == A 
		|| key == FORWARD || key == BACK)
		e->player.walk_direct = 0;
	if (key == Q || key == D || key == A)
		e->player.walk_sideways = 0;
	if (key == RIGHT || key == LEFT)
		e->player.turn_direct = 0;
	return (1);
}

int	keyExit(t_elts *e)
{
		clear_map(&e->map, e);
		clear_texture(e);
		if (e->img.img_ptr != NULL)
			mlx_destroy_image(e->win.mlx_ptr, e->img.img_ptr);
		mlx_destroy_window(e->win.mlx_ptr, e->win.win_ptr);
		mlx_destroy_display(e->win.mlx_ptr);
		free(e->win.mlx_ptr);
		exit(0);
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
}

void	player_update(t_elts *e)
{
	
	double	move_step;
	double	new_pos_x;
	double	new_pos_y;
	double	angle;

	e->player.rotate_radius += e->player.turn_direct * e->player.rotate_speed;
	move_step = (double)e->player.walk_direct * e->player.move_speed;

	angle = e->player.walk_sideways ? M_PI / 2 : 0;
	new_pos_x = e->player.pos.x + cos(e->player.rotate_radius + angle) * move_step;
	new_pos_y = e->player.pos.y + sin(e->player.rotate_radius + angle) * move_step;
	if (is_wall(new_pos_x, new_pos_y, e) == 0)
	{
		e->player.pos.x = new_pos_x;
		e->player.pos.y = new_pos_y;
	}
}

void	put_pixel(t_elts *e, int x, int y, int color)
{
	char	*pix;

	pix = e->img.addr + (y * e->img.size_line + x * (e->img.bpp / 8));
	*(int*)pix = color;
}

void	draw_rect(int x, int start, t_elts *e, int color)
{
	double i = 0.0;
	if (start < 0)
		start = 0;
	if (e->ray.wall_height > e->win.y)
		e->ray.wall_height = e->win.y;
	while (i < e->ray.wall_height)
	{
		put_pixel(e, x, start, color);
		i+= 1.0;
		start += 1;
	}
}

void	cast_all_rays(t_elts *e)
{
	int x = -1;
	e->ray.angle = e->player.rotate_radius - (e->player.fov / 2);
	while (++x < e->win.x)
	{
		init_ray(&e->ray);
		ray_cast(e, x);
		e->ray.angle += e->player.fov / e->win.x;	
	}
}

void	draw_rect2(t_elts *e)
{
	int	i = -1;
	int	color = 0x000000;
	while (++i < (e->win.y))
	{
		int	j = -1;
		while (++j < (e->win.x))
			put_pixel(e, j, i, color);
	}
}

int	update(t_elts *e)
{
	player_update(e);
	draw_rect2(e);
	cast_all_rays(e);
//	map_render(e);
//	player_render(e);
	mlx_put_image_to_window(e->win.mlx_ptr, e->win.win_ptr, e->img.img_ptr, 0, 0);
	return (1);
}

