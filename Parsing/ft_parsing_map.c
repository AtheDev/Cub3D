/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 09:58:46 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/19 16:34:01 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*ft_new_and_lstadd_back(t_map *map, char *content)
{
	t_map	*new;
	t_map	*first_elt;

	if (!content)
		return (NULL);
	if (!(new = malloc(sizeof(t_map))))
		return (NULL);
	new->content = content;
	new->next = NULL;
	if (!map->content)
	{
		map->content = new->content;
		map->next = NULL;
		free(new);
	}
	else
	{
		first_elt = map;
		while (map->next)
			map = map->next;
		map->next = new;
		map = first_elt;
	}
	return (new);
}

int		check_all(t_elts *elts)
{
	int	i;
	int	j;

	j = -1;
	while (++j < elts->height)
	{
		i = 0;
		while (i < elts->width)
		{
			if (elts->tab[j][i] == -16 || elts->tab[j][i] == 0 ||
			elts->tab[j][i] == 1 || elts->tab[j][i] == 21 ||
			elts->tab[j][i] == 30 || elts->tab[j][i] == 35 ||
			elts->tab[j][i] == 39 || elts->tab[j][i] == 2)
				i++;
			else
				return (0);
		}
	}
	if (elts->win.x == 0 || elts->color.f[3] == 0 || elts->color.c[3] == 0
	|| elts->text.north == 0 || elts->text.south == 0 || elts->text.west == 0
	|| elts->text.east == 0 || elts->text.sp == 0 || elts->player.dir == 0)
		return (0);
//	assign_direction(&elts->player);
	return (1);
}

/*void	new_position(t_double *s, double x, double y)
{
	s->x = x;
	s->y = y;
}*/

/*void	assign_direction(t_player *p)
{
	if (p->dir == 30)
	{
		new_position(&p->dir_pl, 0.0, -1.0);
		new_position(&p->plane, p->fov, 0.0);
	}
	else if (p->dir == 35)
	{
		new_position(&p->dir_pl, 0.0, 1.0);
		new_position(&p->plane, p->fov, 0.0);
	}
	else if (p->dir == 39)
	{
		new_position(&p->dir_pl, -1.0, 0.0);
		new_position(&p->plane, 0.0, -p->fov);
	}
	else if (p->dir == 21)
	{
		new_position(&p->dir_pl, 1.0, 0.0);
		new_position(&p->plane, 0.0, p->fov);
	}
}*/

int		is_not_empty_line(char *line, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (line && line[i])
	{
		j = 0;
		while (str[j])
		{
			if (line[i] == str[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		ft_parsing_map(int fd, char *line, t_elts *elts, int count)
{
	elts->width = ft_strlen(line);
	elts->height = 1;
	if (!ft_new_and_lstadd_back(&elts->map, ft_strdup(line)))
		return (0);
	while (get_next_line(fd, &line, 0) > 0)
	{
		if (is_not_empty_line(line, "012NSEW") == 1 && count > 0)
			return (0);
		else if (is_not_empty_line(line, "012NSEW") == 1 && count == 0)
		{
			if (elts->width < ft_strlen(line))
				elts->width = ft_strlen(line);
			elts->height++;
			if (!ft_new_and_lstadd_back(&elts->map, ft_strdup(line)))
				return (0);
		}
		else
			count++;
		free(line);
	}
	free(line);
	if (check_map(elts) == 0 || check_all(elts) == 0)
		return (0);
	return (1);
}
