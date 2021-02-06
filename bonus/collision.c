/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:48:09 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/06 20:22:30 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	collision_east(double x, double y, t_elts *e)
{
	int	map_ind_x;
	int	map_ind_y;

	map_ind_x = floor(x);
	map_ind_y = floor(y);
	if (e->player.walk_sideways == 1 && e->player.walk_direct == 1)
		return (e->tab[(int)(y + 0.1)][map_ind_x] != 0);
	if (e->player.walk_sideways == 1 && e->player.walk_direct == -1)
		return (e->tab[(int)(y - 0.1)][map_ind_x] != 0);
	if (e->player.walk_direct == -1)
		return (e->tab[map_ind_y][(int)(x - 0.1)] != 0);
	if (e->player.walk_direct == 1)
		return (e->tab[map_ind_y][(int)(x + 0.1)] != 0);
	return (0);
}

int	collision_west(double x, double y, t_elts *e)
{
	int	map_ind_x;
	int	map_ind_y;

	map_ind_x = floor(x);
	map_ind_y = floor(y);
	if (e->player.walk_sideways == 1 && e->player.walk_direct == -1)
		return (e->tab[(int)(y + 0.1)][map_ind_x] != 0);
	if (e->player.walk_sideways == 1 && e->player.walk_direct == 1)
		return (e->tab[(int)(y - 0.1)][map_ind_x] != 0);
	if (e->player.walk_direct == -1)
		return (e->tab[map_ind_y][(int)(x + 0.1)] != 0);
	if (e->player.walk_direct == 1)
		return (e->tab[map_ind_y][(int)(x - 0.1)] != 0);
	return (0);
}

int	collision_north(double x, double y, t_elts *e)
{
	int	map_ind_y;
	int	map_ind_x;

	map_ind_y = floor(y);
	map_ind_x = floor(x);
	if (e->player.walk_sideways == 1 && e->player.walk_direct == 1)
		return (e->tab[map_ind_y][(int)(x + 0.1)] != 0);
	if (e->player.walk_sideways == 1 && e->player.walk_direct == -1)
		return (e->tab[map_ind_y][(int)(x - 0.1)] != 0);
	if (e->player.walk_direct == -1)
		return (e->tab[(int)(y + 0.1)][map_ind_x] != 0);
	if (e->player.walk_direct == 1)
		return (e->tab[(int)(y - 0.1)][map_ind_x] != 0);
	return (0);
}

int	collision_south(double x, double y, t_elts *e)
{
	int	map_ind_y;
	int	map_ind_x;

	map_ind_y = floor(y);
	map_ind_x = floor(x);
	if (e->player.walk_sideways == 1 && e->player.walk_direct == 1)
		return (e->tab[map_ind_y][(int)(x - 0.1)] != 0);
	if (e->player.walk_sideways == 1 && e->player.walk_direct == -1)
		return (e->tab[map_ind_y][(int)(x + 0.1)] != 0);
	if (e->player.walk_direct == -1)
		return (e->tab[(int)(y - 0.1)][map_ind_x] != 0);
	if (e->player.walk_direct == 1)
		return (e->tab[(int)(y + 0.1)][map_ind_x] != 0);
	return (0);
}
