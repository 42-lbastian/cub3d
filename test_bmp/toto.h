# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

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
