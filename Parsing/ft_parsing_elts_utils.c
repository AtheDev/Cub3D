/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_elts_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 09:59:57 by adupuy            #+#    #+#             */
/*   Updated: 2020/12/30 12:07:15 by adupuy           ###   ########.fr       */
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

int		size_window(t_elts *elts, char *line, int *i, char coord)
{
	if (elts->win.x != 0 && elts->win.y != 0)
		return (0);
	if (line[++*i] == ' ')
	{
		while (line[*i] == ' ')
			++*i;
		if (line[*i] >= '0' && line[*i] <= '9')
		{
			if (coord == 'x')
			{
				elts->win.x = ft_my_atoi(line, &(*i));
				--*i;
				size_window(elts, line, &(*i), 'y');
			}
			else
				elts->win.y = ft_my_atoi(line, &(*i));
			if (check_error_win(elts, line, &(*i)) == 0)
				return (0);
			return (1);
		}
		return (0);
	}
	return (0);
}

int		color_floor(t_elts *elts, char *line, int *i, int ind)
{
	if ((line[++*i] == ' ' || ind > 0) && elts->color.f[3] == 0)
	{
		while (line[*i] == ' ')
			++*i;
		if (ind == 0 && (check_error_color(line, *i)) == 0)
			return (0);
		if (line[*i] >= '0' && line[*i] <= '9')
		{
			elts->color.f[ind] = ft_my_atoi(line, &(*i));
			if (ind < 2)
			{
				while (line[*i] != ',')
					++*i;
				color_floor(elts, line, &(*i), ++ind);
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

int		color_ceiling(t_elts *elts, char *line, int *i, int ind)
{
	if ((line[++*i] == ' ' || ind > 0) && elts->color.c[3] == 0)
	{
		while (line[*i] == ' ')
			++*i;
		if (ind == 0 && (check_error_color(line, *i)) == 0)
			return (0);
		if (line[*i] >= '0' && line[*i] <= '9')
		{
			elts->color.c[ind] = ft_my_atoi(line, &(*i));
			if (ind < 2)
			{
				while (line[*i] != ',')
					++*i;
				color_ceiling(elts, line, &(*i), ++ind);
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

char	*ft_subtext(char *str, char *line, int *i, int count)
{
	int	tmp;

	if (!(str = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	tmp = -1;
	while (++tmp < count)
		str[tmp] = line[*i - count + tmp];
	str[tmp] = '\0';
	return (str);
}

int		path_texture(t_elts *elts, char *line, int *i)
{
	int	count;
	int	tmp;

	tmp = *i;
	if ((count = check_path(line, &(*i))) == 0)
		return (0);
	if ((line[tmp] == 'N' && elts->text.north != 0) || (line[tmp] == 'W'
	&& elts->text.west != 0) || (line[tmp] == 'E' && elts->text.east != 0)
	|| (line[tmp] == 'S' && line[tmp + 1] == 'O' && elts->text.south != 0)
	|| (line[tmp] == 'S' && line[tmp + 1] == ' ' && elts->text.sp != 0))
		return (0);
	if (line[tmp] == 'N')
		elts->text.north = ft_subtext(elts->text.north, line, &(*i), count);
	if (line[tmp] == 'W')
		elts->text.west = ft_subtext(elts->text.west, line, &(*i), count);
	if (line[tmp] == 'E')
		elts->text.east = ft_subtext(elts->text.east, line, &(*i), count);
	if (line[tmp] == 'S')
	{
		if (line[++tmp] == 'O')
			elts->text.south = ft_subtext(elts->text.south, line, &(*i), count);
		else
			elts->text.sp = ft_subtext(elts->text.sp, line, &(*i), count);
	}
	return (1);
}
