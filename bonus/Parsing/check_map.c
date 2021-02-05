/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:51:42 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/04 21:14:33 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_player(t_elts *e, int count)
{
	int	i;
	int	j;

	j = -1;
	while (++j < e->height)
	{
		i = -1;
		while (++i < e->width)
			if (e->tab[j][i] + 48 == 69 || e->tab[j][i] + 48 == 78 ||
				e->tab[j][i] + 48 == 83 || e->tab[j][i] + 48 == 87)
			{
				count++;
				e->player.pos.x = (double)i + 0.5;
				e->player.pos.y = (double)j + 0.5;
				e->player.dir = e->tab[j][i];
				e->tab[j][i] = 0;
			}
	}
	if (count == 0)
		return (error_msg("Error\nNo player in the map.\n"));
	else if (count > 1)
		return (error_msg("Error\nToo many players in the map.\n"));
	else
		return (1);
}

int		check_column(t_elts *e, int x)
{
	int	i;

	i = -1;
	while (++i < e->height)
	{
		if (e->tab[i][x] == 0 || e->tab[i][x] == 2 || e->tab[i][x] == 21
		|| e->tab[i][x] == 30 || e->tab[i][x] == 35 || e->tab[i][x] == 39
		|| e->tab[i][x] == 3)
			return (msg(1));
	}
	return (1);
}

int		check_space(t_elts *e, int num, int j, int i)
{
	while (++j < e->height)
	{
		i = -1;
		while (++i < e->width)
			if ((j == 0 && e->tab[j][i] == num) ||
			((j == e->height - 1) && e->tab[j][i] == num))
				return (msg(1));
			else if (j > 0 && e->tab[j][i] == num)
				if (e->tab[j][i - 1] == -16
				|| e->tab[j][i + 1] == -16
				|| e->tab[j + 1][i] == -16
				|| e->tab[j - 1][i] == -16
				|| e->tab[j - 1][i - 1] == -16
				|| e->tab[j - 1][i + 1] == -16
				|| e->tab[j + 1][i - 1] == -16
				|| e->tab[j + 1][i + 1] == -16)
					return (msg(1));
	}
	return (1);
}

void	complete_tab(t_elts *e, int j)
{
	int		i;
	int		k;
	t_map	first_elt;

	first_elt = e->map;
	while (++j < e->height)
	{
		i = 0;
		k = -1;
		while (i < e->width && e->map.content[++k] == ' ')
			e->tab[j][i++] = -16;
		while (i < e->width)
		{
			if (e->map.content[k] == '\0')
				while (i < e->width)
					e->tab[j][i++] = -16;
			else
				e->tab[j][i++] = e->map.content[k++] - 48;
		}
		if (e->map.next != NULL)
			e->map = *e->map.next;
	}
	e->map = first_elt;
}

int		check_map(t_elts *e)
{
	int i;
	int j;

	i = -1;
	j = -1;
	resize_map(e, -1, 0);
	if (!(e->tab = malloc(sizeof(int*) * e->height)))
		return (msg(2));
	while (++j < e->height)
		if (!(e->tab[++i] = malloc(sizeof(int**) * e->width)))
			return (msg(2));
	complete_tab(e, -1);
	if ((check_player(e, 0) == 0) || (check_space(e, 0, -1, -1) == 0)
	|| (check_space(e, 2, -1, -1) == 0)
	|| (check_space(e, 3, -1, -1) == 0)
	|| (check_space(e, e->player.dir, -1, -1) == 0)
	|| (check_column(e, e->width - 1) == 0)
	|| (check_column(e, 0) == 0))
		return (0);
	return (1);
}
