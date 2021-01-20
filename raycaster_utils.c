/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 13:05:52 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/20 18:08:20 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(double x, double y, t_elts *e)
{
	int	map_ind_x;
	int	map_ind_y;

	if (x < 0 || x > e->width || y < 0 || y > e->height)
		return (1);
	map_ind_x = floor(x);
	map_ind_y = floor(y);
	if (e->tab[map_ind_y][map_ind_x] != 0)
		return (1);
	return (0);
}

double	normalize_angle(double angle)
{
	double res;

	res = fmod(angle, 2.0 * M_PI);
	if (res < 0.0)
		res = res + (2.0 * M_PI);
	return (res);
}

void	init_ray(t_ray *ray)
{
	ray->angle = normalize_angle(ray->angle);
	ray->down = (ray->angle > 0.0 && ray->angle < M_PI) ? 1 : 0;
	ray->up = (ray->down == 0) ? 1 : 0;
	ray->right = (ray->angle < (0.5 * M_PI) ||
			(ray->angle > (1.5 * M_PI))) ? 1 : 0;
	ray->left = (ray->right == 0) ? 1 : 0;
	ray->dist = 0;
	ray->wall_hit.x = 0.0;
	ray->wall_hit.y = 0.0;
	ray->hit_wall_vert = 0;
	ray->horz_wall_hit.x = 0.0;
	ray->horz_wall_hit.y = 0.0;
	ray->vert_wall_hit.x = 0.0;
	ray->vert_wall_hit.y = 0.0;
	ray->found_horz_wall_hit = 0;
	ray->found_vert_wall_hit = 0;
}

double	dist_between_two_points(double x1, double x2, double y1, double y2)
{
	return (sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))));
}
