/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:18:51 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/17 09:08:53 by adupuy           ###   ########.fr       */
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

int	color_rgb(int t, int r, int g, int b)
{
	int res;

	res = t << 24;
	res = res | r << 16;
	res = res | g << 8;
	res = res |  b;
	return (res);
}
