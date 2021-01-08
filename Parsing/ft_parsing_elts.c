/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_elts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 10:00:14 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/07 14:20:52 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct_elts(t_elts *elts)
{
	elts->win.x = 0;
	elts->win.y = 0;
//	elts->win.mlx_ptr = NULL;
//	elts->win.win_ptr = NULL;
	elts->text.north = 0;
	elts->text.south = 0;
	elts->text.west = 0;
	elts->text.east = 0;
	elts->text.sp = 0;
	elts->color.f[3] = 0;
	elts->color.c[3] = 0;
	elts->map.content = NULL;
	elts->player.dir = 0;
	elts->player.fov = 0.66;
//	elts->player.pos_X = 0;
//	elts->player.pos_Y = 0;
}

int		read_line_next(t_elts *elts, char *line, int i)
{
	int	ret;

	ret = 0;
	if (line[i] == 'R')
		if ((ret = size_window(elts, line, &i, 'x')) == 0)
			printf("Erreur de taille de fenêtre\n");
	if (line[i] == 'F')
		if ((ret = color_floor(elts, line, &i, 0)) == 0)
			printf("Erreur de couleurs sol\n");
	if (line[i] == 'C')
		if ((ret = color_ceiling(elts, line, &i, 0)) == 0)
			printf("Erreur de couleurs plafond\n");
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		if ((ret = path_texture(elts, line, &i)) == 0)
			printf("Erreur de path\n");
	return (ret);
}

int		read_line(t_elts *elts, char *line)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R' || line[i] == 'F' || line[i] == 'C' || line[i] == 'N'
	|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		return (read_line_next(elts, line, i));
	else if (ft_isdigit(line[i]))
		return (-1);
	else
		return (0);
}

int		ft_parsing_elts(t_elts *elts, char *str)
{
	char	*line;
	int		fd;
	int		ret_rl;

	//init_struct_elts(elts);
	if ((fd = open(str, O_RDONLY)) == -1 || read(fd, NULL, 0) == -1)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		if ((ret_rl = read_line(elts, line)) < 0)
			break ;
		free(line);
	}
	if (ret_rl < 0)
	{
		if ((ft_parsing_map(fd, line, elts)) == 0)
			printf("Erreur dans la map\n");
	}
	else
		printf("Erreur\n");
	free(line);
	printf("OK\n");
	close(fd);
	return (1);
}
