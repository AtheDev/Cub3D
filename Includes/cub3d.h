/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:42:47 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/07 20:10:31 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"

typedef struct	s_vect
{
	double	x;
	double	y;
}			t_vect;

typedef struct	s_pos
{
	int	x;
	int	y;
}			t_pos;

typedef	struct	s_player
{
//	double	pos_x;
//	double	pos_y;
	t_vect	pos;
	int	dir;
//	double	dir_x;
//	double	dir_y;
	t_vect	dir_pl;
//	double	plane_x;
//	double	plane_y;
	t_vect	plane;
	double	camera;
//	double	ray_dir_x;
//	double	ray_dir_y;
	t_vect	ray;
//	double	side_dist_x;
//	double	side_dist_y;
	t_vect	side_dist;
//	double	delta_dist_x;
//	double	delta_dist_y;
	t_vect	delta_dist;
	double	perp_wall_dist;
//	int	step_x;
//	int	step_y;
	t_pos	step;
	t_pos	square_map;
	double	fov;
	int	hit;
	int	side;
	int	line_h;
	t_pos	draw;
//	int	draw_s;
//	int	draw_e;
//	int	x;
//	int	y;
//	double	speed;
//	double	angle;
//	double rotate_speed;
}				t_player;

typedef struct	s_map
{
	char			*content;
	struct s_map	*next;
}				t_map;

typedef struct	s_win
{
	int	x;
	int	y;
	void	*mlx_ptr;
	void	*win_ptr;
	double	ratio;
}				t_win;

typedef struct	s_color
{
	int	f[4];
	int	c[4];
}				t_color;

typedef struct	s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sp;
}				t_texture;

typedef struct	s_elts
{
	t_win		win;
	t_color		color;
	t_texture	text;
	t_player	player;
	t_map		map;
	int			**tab;
	int			width;
	int			height;
}				t_elts;

/*
	********** GNL **********
*/
int				get_next_line(int fd, char **line);
int				ft_is_end_line(char *str);
int				ft_new_line(char **str, char **line, int ret, int count);
char			*ft_my_substr(char *s, int start, int len);
char			*ft_my_strjoin(char *s1, char *s2);

/*
	********* PARSING_ELTS *********
*/
void			init_struct_elts(t_elts *elts);
int				ft_parsing_elts(t_elts *elts, char *str);
int				read_line(t_elts *elts, char *line);

/*
	********* PARSING_ELTS_UTILS *********
*/
int				ft_my_atoi(char *line, int *i);
int				size_window(t_elts *elts, char *line, int *i, char coord);
int				color_floor(t_elts *elts, char *line, int *i, int ind);
int				color_ceiling(t_elts *elts, char *lne, int *i, int ind);
int				path_texture(t_elts *elts, char *line, int *i);

/*
	********* PARSING_MAP *********
*/
int				ft_parsing_map(int fd, char *line, t_elts *elts);
t_map			*ft_new_and_lstadd_back(t_map *map, char *content);
int				check_all(t_elts *elts);

/*
	********* CHECK_ERRORS *********
*/
int				check_error_win(t_elts *elts, char *line, int *i);
int				check_error_color(char *line, int i);
int				check_value_color(t_elts *elts, int num);
int				check_path(char *line, int *i);

/*
	********* CHECK_MAP *********
*/
int				check_map(t_elts *elts);
int				complete_tab(t_elts *elts, int j);
int				check_space(t_elts *elts, int num);
int				check_column(t_elts *elts);
int				check_player(t_elts *elts);

/*
	********** RAYCASTER **********
*/
int				raycaster(t_elts *e);
void			find_delta(t_player *p);
void			dind_side(t_player *p);
void			raytracing(t_elts *e);
void			before_drawing(t_player *p, t_win *win);

/*
	********** DRAW **********
*/
void			vertical_line_draw(t_elts *e, int x);

#endif
