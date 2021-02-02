/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_elts_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 09:59:57 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/02 11:12:12 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		size_window(t_elts *e, char *line, int i)
{
	if (e->win.x != 0 && e->win.y != 0)
		return (0);
	if (line[++i] == ' ')
	{
		while (line[i] == ' ')
			++i;
		if (line[i] >= '0' && line[i] <= '9')
			e->win.x = ft_my_atoi(line, &i);
		while (line[i] == ' ')
			++i;
		if (line[i] >= '0' && line[i] <= '9')
			e->win.y = ft_my_atoi(line, &i);
		if (check_error_win(e, line, i) == 0)
			return (0);
		return (1);
	}
	return (0);
}

int		color_floor(t_elts *e, char *line, int i, int ind)
{
	if ((line[++i] == ' ' || ind > 0) && e->color.f[3] == 0)
	{
		while (line[i] == ' ')
			++i;
		if (ind == 0 && (check_error_color(line, i)) == 0)
			return (0);
		if (line[i] >= '0' && line[i] <= '9')
		{
			e->color.f[ind] = ft_my_atoi(line, &i);
			if (ind < 2)
			{
				while (line[i] != ',')
					++i;
				color_floor(e, line, i, ++ind);
			}
			e->color.f[3] = 1;
			if (check_value_color(e, 1) == 0)
				return (0);
			return (1);
		}
		return (0);
	}
	return (0);
}

int		color_ceiling(t_elts *e, char *line, int i, int ind)
{
	if ((line[++i] == ' ' || ind > 0) && e->color.c[3] == 0)
	{
		while (line[i] == ' ')
			++i;
		if (ind == 0 && (check_error_color(line, i)) == 0)
			return (0);
		if (line[i] >= '0' && line[i] <= '9')
		{
			e->color.c[ind] = ft_my_atoi(line, &i);
			if (ind < 2)
			{
				while (line[i] != ',')
					++i;
				color_ceiling(e, line, i, ++ind);
			}
			e->color.c[3] = 1;
			if (check_value_color(e, 0) == 0)
				return (0);
			return (1);
		}
		return (0);
	}
	return (0);
}

char	*ft_subtext(char *str, char *line, int i, int count)
{
	int	tmp;

	if (!(str = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	while (line[i] == ' ')
		i++;
	tmp = -1;
	while (++tmp < count)
		str[tmp] = line[i++];
	str[tmp] = '\0';
	return (str);
}

int		path_texture(t_elts *e, char *line, int i)
{
	int	count;

	if ((count = check_path(line, i)) == 0)
		return (0);
	if ((line[i] == 'N' && e->text.north != 0) || (line[i] == 'W'
	&& e->text.west != 0) || (line[i] == 'E' && e->text.east != 0)
	|| (line[i] == 'S' && line[i + 1] == 'O' && e->text.south != 0)
	|| (line[i] == 'S' && line[i + 1] == ' ' && e->text.sp != 0))
		return (0);
	if (line[i] == 'N')
		e->text.north = ft_subtext(e->text.north, line, i + 2, count);
	if (line[i] == 'W')
		e->text.west = ft_subtext(e->text.west, line, i + 2, count);
	if (line[i] == 'E')
		e->text.east = ft_subtext(e->text.east, line, i + 2, count);
	if (line[i] == 'S')
	{
		if (line[++i] == 'O')
			e->text.south = ft_subtext(e->text.south, line, i + 1, count);
		else
			e->text.sp = ft_subtext(e->text.sp, line, i + 1, count);
	}
	return (1);
}
