/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:13:43 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/20 10:00:07 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_x(t_elts *e, t_text_data *text)
{
	int	res;

	if (e->ray.hit_wall_vert == 1)
		res = fmod(e->ray.wall_hit.y, 1) * text->width;
	else
		res = fmod(e->ray.wall_hit.x, 1) * text->width;
	return (res);
}

int	find_y(int y, t_elts *e, t_text_data *text)
{
	int	res;

	res = (y + e->ray.wall_height / 2 - e->win.y / 2) *
		(text->height / e->ray.wall_height);
	if (res < 0)
		res = 0;
	return (res);
}

int	find_color(int x, int y, t_text_data *text)
{
	char	*dst;
	int	texture_color;
	
	dst = text->addr + (y * text->size_line + x * (text->bpp / 8));
	texture_color = (*(unsigned int*)dst);
	return (texture_color);
}
