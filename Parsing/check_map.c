/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:51:42 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/18 13:39:05 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_player(t_elts *elts)
{
	int	i;
	int	j;
	int	count;

	j = -1;
	count = 0;
	while (++j < elts->height)
	{
		i = -1;
		while (++i < elts->width)
			if (elts->tab[j][i] + 48 == 69 || elts->tab[j][i] + 48 == 78 ||
				elts->tab[j][i] + 48 == 83 || elts->tab[j][i] + 48 == 87)
			{
				count++;
				elts->player.pos.x = (double)i + 0.5;
				elts->player.pos.y = (double)j + 0.5;
				elts->player.dir = elts->tab[j][i];
				elts->tab[j][i] = 0;
			}
	}
	if (count == 1)
		return (1);
	return (0);
}

int	check_column(t_elts *elts)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (++i < elts->width)
	{
		j = 0;
		while (j < elts->height)
		{
			if (j + 1 == elts->height && count != 0)
				return (0);
			else if (elts->tab[j][i] != -16)
			{
				count++;
				break ;
			}
			else
				j++;
		}
	}
	return (1);
}

int	check_space(t_elts *elts, int num)
{
	int	i;
	int	j;

	j = -1;
	while (++j < elts->height)
	{
		i = -1;
		while (++i < elts->width)
		{
			if ((j == 0 && elts->tab[j][i] == num) ||
			((j == elts->height - 1) && elts->tab[j][i] == num))
				return (0);
			else if (j > 0 && elts->tab[j][i] == num)
				if (elts->tab[j][i - 1] == -16
				|| elts->tab[j][i + 1] == -16
				|| elts->tab[j + 1][i] == -16
				|| elts->tab[j - 1][i] == -16
				|| elts->tab[j - 1][i - 1] == -16
				|| elts->tab[j - 1][i + 1] == -16
				|| elts->tab[j + 1][i - 1] == -16
				|| elts->tab[j + 1][i + 1] == -16)
					return (0);
		}
	}
	return (1);
}

int	complete_tab(t_elts *elts, int j)
{
	int	i;
	int	k;
	t_map	first_elt;

	first_elt = elts->map;
	while (++j < elts->height)
	{
		i = 0;
		k = -1;
		while (i < elts->width && elts->map.content[++k] == ' ')
		{
			elts->tab[j][i++] = -16;
			if ((i + 1) == elts->width)
				return (0);
		}
		while (i < elts->width)
		{
			if (elts->map.content[k] == '\0')
				while (i < elts->width)
					elts->tab[j][i++] = -16;
			else
				elts->tab[j][i++] = elts->map.content[k++] - 48;
		}
		if (elts->map.next != NULL)
			elts->map = *elts->map.next;
	}
	elts->map = first_elt;
	return (1);
}

int	check_map(t_elts *elts)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (!(elts->tab = malloc(sizeof(int*) * elts->height)))
		return (0);
	while (++j < elts->height)
		if (!(elts->tab[++i] = malloc(sizeof(int**) * elts->width)))
			return (0);
	if ((complete_tab(elts, -1) == 0) || (check_player(elts) == 0)
	|| ((check_space(elts, 0) == 0) || (check_space(elts, 2) == 0)
	|| (check_space(elts, elts->player.dir)) == 0) ||
	(check_column(elts) == 0))
		return (0);
	return (1);
}
