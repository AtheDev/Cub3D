/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:21:08 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/06 12:22:23 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_error_color_next(char *line, int *i)
{
	if (line[*i] == ' ')
		while (line[*i] == ' ')
			++*i;
	if (line[*i] != ',')
		return (0);
	++*i;
	while (line[*i] == ' ')
		++*i;
	if (ft_isdigit(line[*i]))
		while (ft_isdigit(line[*i]))
			++*i;
	else
		return (0);
	return (1);
}
