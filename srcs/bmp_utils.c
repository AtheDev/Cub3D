/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:14:36 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/29 10:49:33 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_in_char(int file_size, unsigned char *file_header, int start)
{
	int	i;

	i = -1;
	while (++i < 4)
		file_header[start++] = (unsigned char)(file_size >> (i * 8));
}

void	init_corr_pad(char corr_pad[4])
{
	corr_pad[0] = 0;
	corr_pad[1] = 3;
	corr_pad[2] = 2;
	corr_pad[3] = 1;
}
