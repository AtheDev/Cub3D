/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_elts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 10:00:14 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/04 21:15:23 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct_elts(t_elts *e)
{
	e->win.x = 0;
	e->win.y = 0;
	e->text.north = 0;
	e->text.south = 0;
	e->text.west = 0;
	e->text.east = 0;
	e->text.sp = 0;
	e->text.sp2 = 0;
	e->text_data_n.text_ptr = NULL;
	e->text_data_s.text_ptr = NULL;
	e->text_data_w.text_ptr = NULL;
	e->text_data_e.text_ptr = NULL;
	e->text_sprite.text_ptr = NULL;
	e->text_sprite2.text_ptr = NULL;
	e->tab_sp = NULL;
	e->color.f[3] = 0;
	e->color.c[3] = 0;
	e->map.content = NULL;
	e->tab = NULL;
	e->player.dir = 0;
	e->player.fov = 60 * (M_PI / 180);
	e->img.img_ptr = NULL;
	e->win.win_ptr = NULL;
	e->win.mlx_ptr = NULL;
}

int		read_line_next(t_elts *e, char *line, int i)
{
	if (line[i] == 'R')
		if ((size_window(e, line, i)) == 0)
			return (msg2(1));
	if (line[i] == 'F')
	{
		if (color_floor(e, line, i, 0) == 0)
			return (msg2(2));
		else
			e->color.f_color = color_rgb(0, e->color.f[0],
			e->color.f[1], e->color.f[2]);
	}
	if (line[i] == 'C')
	{
		if (color_ceiling(e, line, i, 0) == 0)
			return (msg2(3));
		else
			e->color.c_color = color_rgb(0, e->color.c[0],
			e->color.c[1], e->color.c[2]);
	}
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		if (path_texture(e, line, i) == 0)
			return (msg2(4));
	return (1);
}

int		read_line(t_elts *e, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R' || line[i] == 'F' || line[i] == 'C' || line[i] == 'N'
	|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		return (read_line_next(e, line, i));
	else if (ft_isdigit(line[i]))
		return (-1);
	else if (line[i] == '\0' && i == 0)
		return (1);
	else
		return (msg(5));
}

int		parse_elts(int *stop, int fd, t_elts *e, char **line)
{
	int ret_rl;

	ret_rl = 0;
	while (get_next_line(fd, line, ret_rl) > 0)
	{
		ret_rl = read_line(e, *line);
		if (ret_rl >= 0)
			free(*line);
		if (ret_rl == 0)
		{
			*stop = 1;
			break ;
		}
	}
	return (ret_rl);
}

int		ft_parsing_elts(t_elts *e, char *str)
{
	char	*line;
	int		fd;
	int		ret_rl;
	int		stop;

	stop = 0;
	if ((fd = open(str, O_RDONLY)) == -1 || read(fd, NULL, 0) == -1)
		return (error_msg("Error\nProblem opening file.\n"));
	ret_rl = parse_elts(&stop, fd, e, &line);
	if (ret_rl < 0)
	{
		if ((ft_parsing_map(fd, line, e)) == 0)
			stop = 1;
	}
	else if (ret_rl != -1 && ret_rl != 0)
	{
		error_msg("Error\nThe file doesn't contain a map.\n");
		stop = 1;
		free(line);
	}
	if ((stop == 1 && ret_rl >= 0) || ret_rl != -1)
		get_next_line(fd, &line, 2);
	close(fd);
	return (stop == 1 ? 0 : 1);
}
