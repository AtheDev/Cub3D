/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:21:16 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/07 20:11:10 by adupuy           ###   ########.fr       */
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
	raycaster(&e);
	mlx_loop(e.win.mlx_ptr);
	return (EXIT_SUCCESS);
}
