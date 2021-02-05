/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 09:35:24 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/04 17:05:11 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, t_elts *e)
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
		key_exit(e);
	return (1);
}

int		key_release(int key, t_elts *e)
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

int		key_exit(t_elts *e)
{
	clear_text(e);
	clear_map(&e->map, e, -1);
	clear_texture(e);
	if (e->img.img_ptr != NULL)
		mlx_destroy_image(e->win.mlx_ptr, e->img.img_ptr);
	if (e->win.win_ptr != NULL)
		mlx_destroy_window(e->win.mlx_ptr, e->win.win_ptr);
	if (e->win.mlx_ptr != NULL)
	{
		mlx_destroy_display(e->win.mlx_ptr);
		free(e->win.mlx_ptr);
	}
	exit(0);
	return (1);
}

void	player_update(t_elts *e)
{
	double	move_step;
	double	new_pos_x;
	double	new_pos_y;
	double	angle;

	e->player.rotate_radius += e->player.turn_direct * e->player.rotate_speed;
	move_step = (double)e->player.walk_direct * e->player.move_speed;
	angle = e->player.walk_sideways == 1 ? M_PI / 2 : 0;
	new_pos_x = e->player.pos.x + cos(e->player.rotate_radius + angle)
		* move_step;
	new_pos_y = e->player.pos.y + sin(e->player.rotate_radius + angle) *
		move_step;
	if (is_wall2(new_pos_x, new_pos_y, e) == 0)
	{
		e->player.pos.x = new_pos_x;
		e->player.pos.y = new_pos_y;
	}
}

int		update(t_elts *e)
{
	double	buff[e->win.x];

	player_update(e);
	draw_rect(e);
	cast_all_rays(e, buff);
	render_sprites(buff, e);
	mlx_put_image_to_window(e->win.mlx_ptr,
				e->win.win_ptr, e->img.img_ptr, 0, 0);
	return (1);
}
