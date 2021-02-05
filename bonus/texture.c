/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 21:59:00 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/04 20:58:50 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_texture(t_elts *e)
{
	if (e->text_data_n.text_ptr != NULL)
		mlx_destroy_image(e->win.mlx_ptr, e->text_data_n.text_ptr);
	if (e->text_data_s.text_ptr != NULL)
		mlx_destroy_image(e->win.mlx_ptr, e->text_data_s.text_ptr);
	if (e->text_data_e.text_ptr != NULL)
		mlx_destroy_image(e->win.mlx_ptr, e->text_data_e.text_ptr);
	if (e->text_data_w.text_ptr != NULL)
		mlx_destroy_image(e->win.mlx_ptr, e->text_data_w.text_ptr);
	if (e->text_sprite.text_ptr != NULL)
		mlx_destroy_image(e->win.mlx_ptr, e->text_sprite.text_ptr);
	if (e->text_sprite2.text_ptr != NULL)
		mlx_destroy_image(e->win.mlx_ptr, e->text_sprite2.text_ptr);
}

int		init_texture(char *text_name, t_text_data *t, t_win *win)
{
	t->text_ptr = mlx_xpm_file_to_image(win->mlx_ptr, text_name,
						&t->width, &t->height);
	if (t->text_ptr == NULL)
		return (0);
	t->addr = mlx_get_data_addr(t->text_ptr, &t->bpp,
					&t->size_line, &t->endian);
	return (1);
}

int		texture(t_texture *text, t_elts *e)
{
	if (init_texture(text->north, &e->text_data_n, &e->win) == 0
		|| init_texture(text->south, &e->text_data_s, &e->win) == 0
		|| init_texture(text->east, &e->text_data_e, &e->win) == 0
		|| init_texture(text->west, &e->text_data_w, &e->win) == 0
		|| init_texture(text->sp, &e->text_sprite, &e->win) == 0
		|| init_texture(text->sp2, &e->text_sprite2, &e->win) == 0)
		return (0);
	return (1);
}

void	draw_texture(t_elts *e, int x, t_text_data *text)
{
	int	y;
	int	color;

	if (e->ray.top_pixel < 0)
		e->ray.top_pixel = 0;
	if (e->ray.bottom_pixel > e->win.y)
		e->ray.bottom_pixel = e->win.y;
	e->ray.text_offset.x = find_x(e, text);
	y = e->ray.top_pixel;
	while (y < e->ray.bottom_pixel)
	{
		e->ray.text_offset.y = find_y(y, e, text);
		color = find_color(e->ray.text_offset.x, e->ray.text_offset.y, text);
		put_pixel(e, x, y, color);
		y++;
	}
}

void	choose_texture(t_elts *e, int x)
{
	if (e->ray.hit_wall_vert == 1)
	{
		if (e->ray.left == 1)
			draw_texture(e, x, &e->text_data_w);
		else
			draw_texture(e, x, &e->text_data_e);
	}
	else
	{
		if (e->ray.up == 1)
			draw_texture(e, x, &e->text_data_n);
		else
			draw_texture(e, x, &e->text_data_s);
	}
}
