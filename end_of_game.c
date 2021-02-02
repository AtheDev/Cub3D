/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:26:03 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/02 11:40:02 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_text(t_elts *e)
{
	if (e->text.north != 0)
		free(e->text.north);
	if (e->text.south != 0)
		free(e->text.south);
	if (e->text.east != 0)
		free(e->text.east);
	if (e->text.west != 0)
		free(e->text.west);
	if (e->text.sp != 0)
		free(e->text.sp);
	if (e->tab_sp != NULL)
		free(e->tab_sp);
}

void	clear_map(t_map *map, t_elts *e, int i)
{
	t_map	*lst;
	char	*tmp;

	if (e->tab != NULL)
	{
		while (++i < e->height)
			free(e->tab[i]);
		free(e->tab);
	}
	if (map->content != NULL)
	{
		lst = map->next;
		tmp = map->content;
		free(tmp);
		map = lst;
		while (map != NULL)
		{
			lst = map->next;
			tmp = map->content;
			free(tmp);
			free(map);
			map = lst;
		}
	}
}
