/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_elts_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 09:59:57 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/27 14:37:11 by adupuy           ###   ########.fr       */
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

int		color_floor(t_elts *elts, char *line, int i, int ind)
{
	if ((line[++i] == ' ' || ind > 0) && elts->color.f[3] == 0)
	{
		while (line[i] == ' ')
			++i;
		if (ind == 0 && (check_error_color(line, i)) == 0)
			return (0);
		if (line[i] >= '0' && line[i] <= '9')
		{
			elts->color.f[ind] = ft_my_atoi(line, &i);
			if (ind < 2)
			{
				while (line[i] != ',')
					++i;
				color_floor(elts, line, i, ++ind);
			}
			elts->color.f[3] = 1;
			if (check_value_color(elts, 1) == 0)
				return (0);
			return (1);
		}
		return (0);
	}
	return (0);
}

int		color_ceiling(t_elts *elts, char *line, int i, int ind)
{
	if ((line[++i] == ' ' || ind > 0) && elts->color.c[3] == 0)
	{
		while (line[i] == ' ')
			++i;
		if (ind == 0 && (check_error_color(line, i)) == 0)
			return (0);
		if (line[i] >= '0' && line[i] <= '9')
		{
			elts->color.c[ind] = ft_my_atoi(line, &i);
			if (ind < 2)
			{
				while (line[i] != ',')
					++i;
				color_ceiling(elts, line, i, ++ind);
			}
			elts->color.c[3] = 1;
			if (check_value_color(elts, 0) == 0)
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

int		path_texture(t_elts *elts, char *line, int i)
{
	int	count;

	if ((count = check_path(line, i)) == 0)
		return (0);
	if ((line[i] == 'N' && elts->text.north != 0) || (line[i] == 'W'
	&& elts->text.west != 0) || (line[i] == 'E' && elts->text.east != 0)
	|| (line[i] == 'S' && line[i + 1] == 'O' && elts->text.south != 0)
	|| (line[i] == 'S' && line[i + 1] == ' ' && elts->text.sp != 0))
		return (0);
	if (line[i] == 'N')
		elts->text.north = ft_subtext(elts->text.north, line, i + 2, count);
	if (line[i] == 'W')
		elts->text.west = ft_subtext(elts->text.west, line, i + 2, count);
	if (line[i] == 'E')
		elts->text.east = ft_subtext(elts->text.east, line, i + 2, count);
	if (line[i] == 'S')
	{
		if (line[++i] == 'O')
			elts->text.south = ft_subtext(elts->text.south, line, i + 1, count);
		else
			elts->text.sp = ft_subtext(elts->text.sp, line, i + 1, count);
	}
	return (1);
}
