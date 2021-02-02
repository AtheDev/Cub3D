/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:17:47 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/02 11:17:29 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_error_win(t_elts *e, char *line, int i)
{
	while (line && line[i])
	{
		if (line[i] != ' ')
			return (0);
		++i;
	}
	if (e->win.x == 0 || e->win.y == 0)
		return (0);
	return (1);
}

int	check_error_color(char *line, int i)
{
	int	comma;
	int	number;

	comma = 0;
	number = 0;
	while (line && line[i])
	{
		if (ft_isdigit(line[i]) && (number == 0 ||
			line[i - 1] == ' ' || line[i - 1] == ','))
			number++;
		else if (line[i] == ',')
			comma++;
		else if (line[i] != ',' && line[i] != ' ' && !ft_isdigit(line[i]))
			return (0);
		i++;
	}
	if (number == 3 && comma == 2)
		return (1);
	return (0);
}

int	check_value_color(t_elts *e, int num)
{
	int	i;

	i = -1;
	if (num == 1)
	{
		while (++i < 3)
			if (e->color.f[i] < 0 || e->color.f[i] > 255)
				return (0);
	}
	else
	{
		while (++i < 3)
			if (e->color.f[i] < 0 || e->color.f[i] > 255)
				return (0);
	}
	return (1);
}

int	check_path(char *line, int i)
{
	int	size;

	size = 0;
	if (((line[i] == 'N' || line[i] == 'S') && line[i + 1] == 'O')
		|| (line[i] == 'W' && line[i + 1] == 'E')
		|| (line[i] == 'E' && line[i + 1] == 'A')
		|| (line[i] == 'S' && line[i + 1] == ' '))
	{
		i += 2;
		while (line[i] == ' ' && line[i])
			++i;
		while (ft_isprint(line[i]) && line[i] != ' ')
		{
			size++;
			++i;
		}
		while (line[i])
		{
			if (line[i] != ' ')
				return (0);
			i++;
		}
	}
	return (size);
}

int	check_double_texture(t_elts *e)
{
	if (ft_strcmp(e->text.north, e->text.south) == 0 ||
	ft_strcmp(e->text.north, e->text.east) == 0 ||
	ft_strcmp(e->text.north, e->text.west) == 0 ||
	ft_strcmp(e->text.north, e->text.sp) == 0 ||
	ft_strcmp(e->text.south, e->text.east) == 0 ||
	ft_strcmp(e->text.south, e->text.west) == 0 ||
	ft_strcmp(e->text.south, e->text.sp) == 0 ||
	ft_strcmp(e->text.east, e->text.west) == 0 ||
	ft_strcmp(e->text.east, e->text.sp) == 0 ||
	ft_strcmp(e->text.west, e->text.sp) == 0)
		return (0);
	return (1);
}
