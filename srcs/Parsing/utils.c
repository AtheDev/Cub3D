/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:18:51 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/06 10:53:24 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_my_atoi(char *line, int *i)
{
	int	res;

	res = 0;
	while (line[*i] == '0')
		++*i;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		res = res * 10 + (line[*i] - 48);
		++*i;
	}
	return (res);
}

int		color_rgb(int t, int r, int g, int b)
{
	int res;

	res = t << 24;
	res = res | r << 16;
	res = res | g << 8;
	res = res | b;
	return (res);
}

int		is_a_forbidden_char(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == ' ' || line[i] == '0' || line[i] == '1' ||
		line[i] == '2' || line[i] == 'N' || line[i] == 'S' ||
		line[i] == 'E' || line[i] == 'W')
			i++;
		else
			return (0);
	}
	return (1);
}

void	resize_map(t_elts *e, int i, int k)
{
	t_map	first_elt;

	first_elt = e->map;
	while (++i < e->height - 1)
		e->map = *e->map.next;
	while (e->map.content[k] != '\0')
	{
		if (e->map.content[k] == ' ')
			k++;
		else
			break ;
	}
	if (e->map.content[k] == '\0')
	{
		e->height -= 1;
		e->map = first_elt;
		resize_map(e, -1, 0);
	}
	e->map = first_elt;
	return ;
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] != s2[i])
		return (1);
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (1);
}
