/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:21:16 by adupuy            #+#    #+#             */
/*   Updated: 2021/02/06 16:46:01 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_start(t_elts *e)
{
	mlx_hook(e->win.win_ptr, 2, (1L << 0), &key_press, e);
	mlx_hook(e->win.win_ptr, 3, (1L << 1), &key_release, e);
	mlx_hook(e->win.win_ptr, 33, (1L << 17), &key_exit, e);
	mlx_loop_hook(e->win.mlx_ptr, &update, e);
	mlx_loop(e->win.mlx_ptr);
}

void	first_view(t_elts *e)
{
	double	buff[e->win.x];

	cast_all_rays(e, buff);
	render_sprites(buff, e);
	if (generate_bmp_image(e) == 0)
		error_msg("Error\nProblem while creating bitmap file.\n");
	else
		write(1, "Bitmap file created.\n", 21);
}

void	set_up_the_game(t_elts *e, int save, char *str)
{
	init_struct_elts(e);
	if (ft_parsing_elts(e, str) == 0 || check_open_texture(&e->text) == 0
		|| init_window(&e->win) == 0 || texture(&e->text, e) == 0
		|| init_sprite(e) == 0 || init_win(&e->win, save) == 0
		|| init_image(e) == 0)
		return ;
	init_player(e);
	if (save == 0)
		game_start(e);
	else
		first_view(e);
}

int		main(int argc, char **argv)
{
	t_elts	e;
	int		save;

	save = 0;
	if (argc == 2 || argc == 3)
	{
		if (check_file(argv[1], ".cub") == 0)
			return (error_msg("Error\nIt's not a '.cub' file.\n"));
		if (argc == 3)
		{
			if (ft_strlen(argv[2]) == 6 &&
				ft_strncmp(argv[2], "--save", 6) == 0)
				save = 1;
			else
				return (msg(6));
		}
		set_up_the_game(&e, save, argv[1]);
		key_exit(&e);
	}
	if (argc < 2 || argc > 3)
		return (error_msg("Error\nNumber of arguments is wrong.\n"));
	return (0);
}
