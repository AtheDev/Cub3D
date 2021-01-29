/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:21:16 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/29 15:03:26 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize_window(t_win *win)
{
	int	width_screen;
	int	height_screen;

	mlx_get_screen_size(win->mlx_ptr, &width_screen, &height_screen);
	if (width_screen < win->x)
		win->x = width_screen;
	if (height_screen < win->y)
		win->y = height_screen;
}

int	init_window(t_win *win, int save)
{
	win->mlx_ptr = mlx_init();
	if (win->mlx_ptr == NULL)
		return (0);
	if (save == 0)
	{
		resize_window(win);
		win->win_ptr = mlx_new_window(win->mlx_ptr, win->x, win->y, "cub3d");
		if (win->win_ptr == NULL)
			return (0);
	}
	else
		win->win_ptr = NULL;
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

	if (e->tab_sp != NULL)
		free(e->tab_sp);

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

int	exit_error(char *str, t_elts *e)
{
	write(1, str, ft_strlen(str));
	keyExit(e);
	return (0);
}

void	game_start(t_elts *e)
{
	mlx_hook(e->win.win_ptr, 2, (1L<<0), &keyPress, e);
	mlx_hook(e->win.win_ptr, 3, (1L<<1), &keyRelease, e);
	mlx_hook(e->win.win_ptr, 33, (1L<<17), &keyExit, e);
	mlx_loop_hook(e->win.mlx_ptr, &update, e);
	mlx_loop(e->win.mlx_ptr);
}

int	first_view(t_elts *e)
{
	double	buff[e->win.x];

	cast_all_rays(e, buff);
	render_sprites(buff, e);
	return (generate_bmp_image(e));
}

int	set_up_the_game(t_elts *e, int save, char *str)
{
	init_struct_elts(e);
	if (ft_parsing_elts(e, str) == 0)
		return (0);
	if (init_window(&e->win, save) == 0)
		return (0);
	if (init_image(e) == 0)
		return (0);
	if (texture(&e->text, e) == 0)
	{
		write(1, "Error when setting up textures.\n", 32);
		return (0);
	}
	if (init_sprite(e) == 0)
		return (0);
	init_player(e);
	if (save == 0)
		game_start(e);
	if (save == 1)
		return (first_view(e));
	return (1);
}

int	check_file(char *str, char *name)
{
	int	size;
	int	i;
	int	j;

	size = ft_strlen(str);
	i = size - 4;
	j = 0;
	if (str[i] == name[j])
	{
		if (str[i + 1] == name[1] && str[i + 2] == name[2] && str[i + 3] == name[3])
			return (1);
		else
			return (0);
	}
	return (0);
	
}

int	main(int argc, char **argv)
{
	t_elts	e;
	int	save;

	save = 0;
	if (argc == 2 || argc == 3)
	{
		if (check_file(argv[1], ".cub") == 0)
		{
			write(1, "Error on file name.\n", 20);
			return (EXIT_FAILURE);
		}
	}
	if (argc == 2)
		if (set_up_the_game(&e, save, argv[1]) == 0)
		{
			keyExit(&e);
			return (EXIT_FAILURE);
		}
	if (argc == 3)
	{
		if (ft_strlen(argv[2]) == 6 && ft_strncmp(argv[2], "--save", 6) == 0)
			save = 1;
		if (save == 1 )
		{
			if (set_up_the_game(&e, save, argv[1]) == 0)
				exit_error("Erreur lors de la sauvegarde.\n", &e);
			else
				exit_error("Sauvegarde effectuée.\n", &e);
		}
		else
			return (EXIT_FAILURE);
	}		
	return (EXIT_SUCCESS);
}
