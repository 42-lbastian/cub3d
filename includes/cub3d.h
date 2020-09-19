/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:39:41 by Bastian           #+#    #+#             */
/*   Updated: 2020/09/15 19:12:36 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

typedef struct	s_vect
{
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double raydir_x;
	double raydir_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double camera_x;
}				t_vect;

typedef struct	s_sprite
{
	int	height;
	int width;
	void *sprite;
	unsigned int *data_sp;
	int nb;
	double x;
	double y;
	double inv_det;
	double transform_x;
	double transform_y;
	int		screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
	int		d;
	int		tex_x;
	int		tex_y;
	int **specs;
}				t_sprite;


typedef struct	s_count
{
	double i;
	int l;
	int stripe;
}				t_count;

typedef struct	s_draw
{
	double line_height;
	double draw_start;
	double draw_end;
	unsigned int color;
}				t_draw;

typedef struct	s_move
{
	double move_speed;
	double rot_speed;
}				t_move;

typedef	struct	s_cub
{
	char	path_s[1024];
	char	path_n[1024];
	char	path_w[1024];
	char	path_e[1024];
	char	path_sp[1024];
	int		r[2];
	int		f;
	int		c;
	int		**map;
	int		*size_map;
	char	save;
	int nb_sprites;
}				t_cub;

typedef	struct	s_space
{
	int map_x;
	int map_y;
	double step_x;
	double step_y;
	double wall_dist;
	double old_wall_dist;
	double hit;
	double side;
	double pos_x;
	double pos_y;
}				t_space;

typedef	struct	s_image
{
	void *south;
	void *north;
	void *east;
	void *west;
	unsigned int *data_img;
	unsigned int *data_rendering;
	void *img_rendering;
	int	height;
	int	width;
	int text_x;
	int text_y;
	double text_pos;
	double step;
	double wall_x;
	int bordel; //A CHANGER
	int endian;
	int bpp;
}				t_image;

typedef	struct	s_mxl
{
	void *mlx_init;
	void *mlx_screen;
	t_vect vect;
	t_cub cub;
	t_move move;
	t_draw draw;
	t_space space;
	t_image image;
	t_count count;
	t_sprite sprite;
}				t_mlx;

int				ft_parse(char *str, t_cub *cub, int fd);
size_t			ft_strlen(char *str);
int				ft_strcmp(char *s1, char *s2);
void			ft_putstr(char *str);
int				ft_check_data(t_mlx *mlx);
int				ft_size_map(int *size_map);
int				ft_verif_sprites(t_mlx *mlx);
int				ft_verif_map(t_cub cub);
int				ft_verif_joueur(t_cub cub);
int				ft_parse_fc(int fd, int *fc, int i, char *str);
int				ft_parse_r(int fd, int tab[2]);
int				ft_parse_news(int fd, char path[1024], char ale, t_cub *cub);
int				ft_comp_float(float nb_1, float nb_2);
int				count_lines_map(int fd);
void			init_size_cub(t_cub *cub, int count);
int				ft_raycast_launch(t_mlx *mlx);
void			ft_turn_left(t_mlx **mlx);
void			ft_turn_right(t_mlx **mlx);
void			ft_backward(t_mlx **mlx);
void			ft_forward(t_mlx **mlx);
void			ft_init_position(t_mlx *mlx);
void			ft_init_raycast(t_mlx **mlx);
void			ft_init_value(t_mlx *mlx);
int				ft_give_xy_map(t_cub *cub, int fact);
int				ft_position_player(t_cub *cub);
int				ft_position_sprite(t_mlx **mlx);
void			ft_wall(t_mlx **mlx);
void			ft_wall_2(t_mlx **mlx);
void			ft_wall_text(t_mlx **mlx);
void			ft_draw_image(t_mlx **mlx);
void			ft_sprite(t_mlx **mlx, double dist_buffer[(*mlx)->cub.r[0]], int i, int y);
void			sort_sprites(int *order, double *dist, int nb);
void			ft_direction(t_mlx **mlx);
void			ft_obstacle_calculation(t_mlx **mlx);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd, int nb);
void			ft_print_null(int nb, int fd);
void			free_cub(t_cub *cub);
int				ft_parse_2(char c, t_cub *cub, int fd, int error);
void			ft_calc_sprite_2(t_mlx **mlx);
void			ft_sprite_draw(t_mlx **mlx, int y, double sprite_dist[(*mlx)->sprite.nb], int i);
void			ft_sprite_calc_draw(t_mlx **mlx);
void			ft_sprite_calc_coord(t_mlx **mlx, int i, int sprite_order[(*mlx)->sprite.nb]);
void			ft_sprite_order(t_mlx **mlx, int i, double sprite_dist[(*mlx)->sprite.nb], int sprite_order[(*mlx)->sprite.nb]);
void			ft_magic_bmp(t_mlx **mlx);
int				ft_free_all(t_mlx **mlx);
int				ft_invalid_file(t_mlx **mlx);
int				ft_invalid_arg(void);
void			ft_fuck_norm_27_to_25(t_mlx *mlx);

#endif
