/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 09:58:46 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/01 19:07:30 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*ft_new_and_lstadd_back(t_map *map, char *content)
{
	t_map	*new;
	t_map	*first_elts;

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
		first_elts = map;
		while (map->next)
			map = map->next;
		map->next = new;
		map = first_elts;
	}
	return (new);
}

int		check_all(t_elts *e)
{
	int	i;
	int	j;

	j = -1;
	while (++j < e->height)
	{
		i = 0;
		while (i < e->width)
		{
			if (e->tab[j][i] == -16 || e->tab[j][i] == 0 ||
			e->tab[j][i] == 1 || e->tab[j][i] == 21 ||
			e->tab[j][i] == 30 || e->tab[j][i] == 35 ||
			e->tab[j][i] == 39 || e->tab[j][i] == 2)
				i++;
			else
				return (msg(3));
		}
	}
	if (e->win.x == 0 || e->color.f[3] == 0 || e->color.c[3] == 0
	|| e->text.north == 0 || e->text.south == 0 || e->text.west == 0
	|| e->text.east == 0 || e->text.sp == 0 || e->player.dir == 0)
		return (msg(4));
	if (check_double_texture(e) == 0)
		return (error_msg("Error\nTwo identical textures.\n"));
	return (1);
}

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

void	parse_map(int *stop, int fd, t_elts *e, char **line)
{
	while (get_next_line(fd, line, 0) > 0)
	{
		if (*line[0] != '\0' && is_a_forbidden_char(*line) == 0)
			*stop = 1;
		else if (*line[0] == '\0' || is_not_empty_line(*line, "012NSEW ") == 1)
		{
			if (e->width < (int)ft_strlen(*line))
				e->width = ft_strlen(*line);
			e->height++;
			if (!ft_new_and_lstadd_back(&e->map, ft_strdup(*line)))
				*stop = 1;
		}
		if (*stop != 1)
			free(*line);
		if (*stop == 1)
			break ;
	}
}

int		ft_parsing_map(int fd, char *line, t_elts *e)
{
	int	stop;

	stop = 0;
	e->width = ft_strlen(line);
	e->height = 1;
	if (!ft_new_and_lstadd_back(&e->map, ft_strdup(line)))
		stop = 1;
	free(line);
	if (stop == 0)
		parse_map(&stop, fd, e, &line);
	if (stop == 1)
		get_next_line(fd, &line, 2);
	free(line);
	if (stop == 1)
		return (msg(3));
	if (check_map(e) == 0 || check_all(e) == 0)
		return (0);
	return (1);
}
