/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:42:47 by adupuy            #+#    #+#             */
/*   Updated: 2021/01/29 14:56:09 by adupuy           ###   ########.fr       */
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
# include <limits.h>
# include <mlx.h>
# include "libft.h"

# define W 119
# define A 97
# define S 115
# define D 100
# define Z 122
# define Q 113
# define LEFT 65361
# define FORWARD 65362
# define RIGHT 65363
# define BACK 65364
# define ESC 65307
# define SIZE 32
# define MINI 0.2

# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
# define BPP 3
# define BMP_FILE_NAME "bitmap_image.bmp"

typedef struct	s_double
{
	double	x;
	double	y;
}			t_double;

typedef struct	s_pos
{
	int	x;
	int	y;
}			t_pos;

typedef struct	s_ray
{
	double	angle;
	double	dist;
	t_double	wall_hit;
	t_double	side_dist;
	t_double	step;
	t_double	horz_wall_hit;
	t_double	vert_wall_hit;
	t_double	touch;
	int	found_vert_wall_hit;
	int	found_horz_wall_hit;
	int	hit_wall_vert;
	int	up;
	int	down;
	int	left;
	int	right;
	double	wall_height;
	double	dist_project;
	double	dist_correct;
	int	top_pixel;
	int	bottom_pixel;
	t_pos	text_offset;
}			t_ray;

typedef struct	s_img
{
	void	*img_ptr;
	void	*addr;
	int	bpp;
	int	size_line;
	int	endian;
}			t_img;

typedef struct	s_text_data
{
	void	*text_ptr;
	void	*addr;
	int	bpp;
	int	size_line;
	int	endian;
	int	width;
	int	height;
}			t_text_data;

typedef struct	s_player
{
	t_double	pos;
	t_double	dir_pl;
	int	dir;
	int	turn_direct;
	int	walk_direct;
	int	walk_sideways;
	double	move_speed;
	double	radius;
	double	rotate_radius;
	double	rotate_speed;
	double 	fov;

}			t_player;

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
	int	f_color;
	int	c_color;
}				t_color;

typedef struct	s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sp;
}				t_texture;

typedef struct	s_sprite
{
	t_double	pos;
	double		dist;
	int		visible;
	double		angle;
	int		top_pixel;
	int		bottom_pixel;
	int		width_sprite;
	int		height_sprite;
	t_pos		text_offset;
}				t_sprite;

typedef struct	s_bmp_utils
{
	int	color;
	char	*dst;
	int	nb_pad;
	unsigned char	tab_pixel[3];
	char	corr_pad[4];
}				t_bmp_utils;

typedef struct	s_img_head
{
	int	size_img_head;
	int	width;
	int	height;
	short	nb_plan;
	short	bpp;
	int	compress;
	int	size_img;
	int	res_h;
	int	res_v;
	int	color_pal;
	int	color_imp_pal;
}				t_img_head;

typedef struct	s_bmp_head
{
	char	sign[2];
	int	size_tot;
	int	reserve;
	int	offset_img;
	struct s_img_head	img_head;
}				t_bmp_head;

typedef struct	s_elts
{
	t_win		win;
	t_color		color;
	t_texture	text;
	t_player	player;
	t_ray		ray;
	t_map		map;
	t_img		img;
	t_text_data	text_data_n;
	t_text_data	text_data_s;
	t_text_data	text_data_e;
	t_text_data	text_data_w;
	t_text_data	text_sprite;	
	int			**tab;
	int			width;
	int			height;
	int			num_sp;
	t_sprite	*tab_sp;
	
}				t_elts;

/*
	********** GNL **********
*/
int				get_next_line(int fd, char **line, int ret_rl);
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
int				color_rgb(int t, int r, int g, int b);
int				size_window(t_elts *elts, char *line, int i);
int				color_floor(t_elts *elts, char *line, int i, int ind);
int				color_ceiling(t_elts *elts, char *lne, int i, int ind);
int				path_texture(t_elts *elts, char *line, int i);

/*
	********* PARSING_MAP *********
*/
int				ft_parsing_map(int fd, char *line, t_elts *elts, int count);
t_map			*ft_new_and_lstadd_back(t_map *map, char *content);
int				check_all(t_elts *elts);
void			new_position(t_double *s, double x, double y);

/*
	********* CHECK_ERRORS *********
*/
int				check_error_win(t_elts *elts, char *line, int i);
int				check_error_color(char *line, int i);
int				check_value_color(t_elts *elts, int num);
int				check_path(char *line, int i);

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
void			ray_cast(t_elts *e, int x);
void			find_side_horz(t_elts *e, int u);
void			find_side_vert(t_elts *e, int u);
void			compare_dist(t_elts *e);

/*
	********** DRAW **********
*/
void			init_player(t_elts *e);
void			draw_rect(int x, int start, t_elts *e, int color);
int				update(t_elts *e);
int				keyPress(int key, t_elts *param);
int				keyRelease(int key, t_elts *param);
int				keyExit(t_elts *e);
void			cast_all_rays(t_elts *e, double *buff);

/*
	********** RAYCASTER_UTILS **********
*/
int				is_wall(double x, double y, t_elts *e);
double			normalize_angle(double angle);
void			init_ray(t_ray *ray);
double			dist_between_two_points
				(double x1, double x2, double y1, double y2);
void			choose_texture(t_elts *e, int x);

/*
	********** DRAW_MINIMAP **********
*/
void			player_render(t_elts *e);
void			map_render(t_elts *e);
void			ray_render(t_elts *e);


void			clear_map(t_map *map, t_elts *e);
void			put_pixel(t_elts *e, int x, int y, int color);


/*
	********** TEXTURE **********
*/
int				texture(t_texture *text, t_elts *e);
int				init_texture(char *text_name, t_text_data *t, t_win *win);
int				check_open_file(char *name);
void			clear_texture(t_elts *e);
void			draw_texture(t_elts *e, int x, t_text_data *text);

/*
	********** TEXTURE_UTILS **********
*/
int				find_x(t_elts *e, t_text_data *text);
int				find_y(int y, t_elts *e, t_text_data *text);
int				find_color(int x, int y, t_text_data *text);
void			init_text_ptr(t_elts *e);

/*
	********** SPRITE **********
*/
int				init_sprite(t_elts *e);
void			render_sprites(double *buff, t_elts *e);

/*
	********** SPRITE_UTILS **********
*/
int				count_sprite(t_elts *e);
void			complete_tab_sprite(t_elts *e);
void			find_angle(t_elts *e, int i);
void			sort_sprites(t_elts *e);
void			find_dist(t_elts *e);

/*
	********** BMP **********
*/
int	generate_bmp_image(t_elts *e);

/*
	********** BMP_UTILS **********
*/
void			set_in_char(int file_size, unsigned char *file_header, int start);
void			init_corr_pad(char corr_pad[4]);

/*
	********** MAIN **********
*/
int				exit_error(char *str, t_elts *e);
int				check_file(char *str, char *name);
#endif
