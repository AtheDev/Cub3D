/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:06:45 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/02 13:33:48 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_bmp_file_header
	(int height, int width, unsigned char *file_header)
{
	int	file_size;

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE +
		(BPP * width * height + (((4 - ((width * BPP) % 4)) % 4) * height));
	ft_bzero(file_header, FILE_HEADER_SIZE);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	set_in_char(file_size, file_header, 2);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
}

void	create_bmp_info_header
	(int height, int width, unsigned char *info_header)
{
	ft_bzero(info_header, INFO_HEADER_SIZE);
	info_header[0] = (unsigned char)(INFO_HEADER_SIZE);
	set_in_char(width, info_header, 4);
	set_in_char(height, info_header, 8);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(BPP * 8);
	info_header[20] = (unsigned char)(BPP * width * height +
			((4 - ((width * BPP) % 4)) % 4) * height);
}

void	create_bmp_image(t_elts *e, int fd)
{
	int			y;
	int			x;
	t_bmp_utils	bmp;

	init_corr_pad(bmp.corr_pad);
	bmp.nb_pad = bmp.corr_pad[(3 * e->win.x) % 4];
	y = e->win.y;
	while (--y >= 0)
	{
		x = -1;
		while (++x < e->win.x)
		{
			bmp.dst = e->img.addr + (y * e->img.size_line + x *
			(e->img.bpp / 8));
			bmp.color = (*(unsigned int*)bmp.dst);
			bmp.tab_pixel[2] = (bmp.color & 0xFF0000) >> 16;
			bmp.tab_pixel[1] = (bmp.color & 0x00FF00) >> 8;
			bmp.tab_pixel[0] = (bmp.color & 0x0000FF);
			write(fd, bmp.tab_pixel, 3);
		}
		ft_bzero(bmp.tab_pixel, 3);
		write(fd, bmp.tab_pixel, bmp.nb_pad);
	}
}

int		generate_bmp_image(t_elts *e)
{
	unsigned char	file_header[FILE_HEADER_SIZE];
	unsigned char	info_header[INFO_HEADER_SIZE];
	int				fd;

	create_bmp_file_header(e->win.y, e->win.x, file_header);
	create_bmp_info_header(e->win.y, e->win.x, info_header);
	fd = open(BMP_FILE_NAME, O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
		return (0);
	write(fd, file_header, FILE_HEADER_SIZE);
	write(fd, info_header, INFO_HEADER_SIZE);
	create_bmp_image(e, fd);
	if ((close(fd)) == -1)
		return (0);
	return (1);
}
