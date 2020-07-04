/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:39:41 by Bastian           #+#    #+#             */
/*   Updated: 2020/07/02 12:35:42 by Bastian          ###   ########.fr       */
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

typedef struct	s_count
{
	double i;
	int l;
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
	int crouch;
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
	void *sprite;
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

#endif
