/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:21:16 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/20 19:17:53 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(t_win *win)
{
	win->mlx_ptr = mlx_init();
	if (win->mlx_ptr == NULL)
		return (0);
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->x, win->y, "cub3d");
	if (win->win_ptr == NULL)
		return (0);
	return (1);
}

int	init_image(t_elts *e)
{
	e->img.img_ptr = mlx_new_image(e->win.mlx_ptr, e->win.x, e->win.y);
	if (e->img.img_ptr == NULL)
		return (0);
	e->img.addr = mlx_get_data_addr(e->img.img_ptr, &(e->img.bpp),
				&(e->img.size_line), &(e->img.endian));
	return (1);
}

void	clear_map(t_map *map, t_elts *e)
{
	t_map	*lst;
	char *tmp;
	int i;

	i = -1;
	while (++i < e->height)
		free(e->tab[i]);
	free(e->tab);
	lst = map->next;
	tmp = map->content;
	free(tmp);
	map = lst;
	while (map != NULL)
	{
		lst = map->next;
		tmp = map->content;
		free(tmp);
		free(map);
		map = lst;
	}
free(e->text.north);
free(e->text.south);
free(e->text.east);
free(e->text.west);
free(e->text.sp);
}

int	main(int argc, char **argv)
{
	t_elts	e;

	if (argc == 2)
	{
		init_struct_elts(&e);
		if (ft_parsing_elts(&e, argv[1]) == 0)
			return (EXIT_FAILURE);
	}
	if (init_window(&e.win) == 0)
		return (EXIT_FAILURE);
	if (init_image(&e) == 0)
		return (EXIT_FAILURE);
	if (texture(&e.text, &e) == 0)
		return (EXIT_FAILURE);
	init_player(&e);
	mlx_hook(e.win.win_ptr, 2, (1L<<0), &keyPress, &e);
	mlx_hook(e.win.win_ptr, 3, (1L<<1), &keyRelease, &e);
	mlx_hook(e.win.win_ptr, 33, (1L<<17), &keyExit, &e);
	mlx_loop_hook(e.win.mlx_ptr, &update, &e);
	mlx_loop(e.win.mlx_ptr);
	return (EXIT_SUCCESS);
}
