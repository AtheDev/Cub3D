/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 16:18:22 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/02 09:56:00 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(char *str, char *name)
{
	int	size;
	int	i;

	size = ft_strlen(str);
	i = size - 4;
	if (str[i] == name[0])
	{
		if (str[i + 1] == name[1] && str[i + 2] == name[2] &&
			str[i + 3] == name[3])
			return (1);
		else
			return (0);
	}
	return (0);
}

int	msg(int num_msg)
{
	if (num_msg == 1)
	{
		error_msg("Error\nThe map is not closed by walls or ");
		error_msg("one of elements is in contact with space.\n");
	}
	if (num_msg == 2)
		error_msg("Error\nProblem with memory allocation.\n");
	if (num_msg == 3)
	{
		error_msg("Error\nThe map contains an an line doesn't ");
		error_msg("contain the allowed characters.\n");
	}
	if (num_msg == 4)
		error_msg("Error\nOne of the map description elements is missing.\n");
	if (num_msg == 5)
	{
		error_msg("Error\nLine not really empty or wrong identifier ");
		error_msg("or player outside the map.\n");
	}
	if (num_msg == 6)
		error_msg("Error\nThe argument for saving is wrong.\n");
	return (0);
}

int	msg2(int num_msg)
{
	if (num_msg == 1)
		(error_msg("Error\nWindow resolution wrong or defined twice.\n"));
	if (num_msg == 2)
		(error_msg("Error\nFloor color wrong or defined twice.\n"));
	if (num_msg == 3)
		(error_msg("Error\nCeiling color wrong or defined twice.\n"));
	if (num_msg == 4)
		(error_msg("Error\nWrong textures or defined twice.\n"));
	return (0);
}

int	error_msg(char *str)
{
	write(1, str, ft_strlen(str));
	return (0);
}
