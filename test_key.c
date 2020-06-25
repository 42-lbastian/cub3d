#include "includes/cub3d.h"
#include <string.h>

#define FACT 1

typedef struct  s_nik {
	void    *image;
	int dist_wall;
	unsigned int *data;
	int reso2;
	int reso;
}				t_nik;

typedef struct  s_vars {
	void    *init;
	void    *win;
	t_nik   nik;
}          t_vars;

int             close_mlx(int keycode, t_vars **vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window((*vars)->init, (*vars)->win);
		exit(0);
	}
	if (keycode == 119)
		(*vars)->nik.dist_wall++;
	if (keycode == 115)
		(*vars)->nik.dist_wall--;
	return (1);
}

int				toto(t_vars **vars)
{
	int i = 0;
	int bordel;
	for (int y = 0; y < (*vars)->nik.reso2; y+=(*vars)->nik.dist_wall)
	{
		for (int x = 0; x < (*vars)->nik.reso; x+=(*vars)->nik.dist_wall)
		{
				mlx_pixel_put((*vars)->init, (*vars)->win, x/(*vars)->nik.dist_wall, y/(*vars)->nik.dist_wall, (*vars)->nik.data[i]);
				if (x + (*vars)->nik.dist_wall <= (*vars)->nik.reso)
					i += (*vars)->nik.dist_wall;
				else
					i += (*vars)->nik.reso - x;
		}
		i += ((*vars)->nik.dist_wall - 1) * (*vars)->nik.reso;
	}

	return (1);
}

int             main(void)
{
	t_vars		*vars;


	vars = malloc(sizeof(t_vars));

	vars->nik.dist_wall = 1;
	int bpp;
	int sizeline;
	int endian;
	vars->init = mlx_init();
	vars->win = mlx_new_window(vars->init, 1080, 720, "Hello world!");
	mlx_hook(vars->win, 2, 1L<<0, close_mlx, &vars);
	vars->nik.image = mlx_xpm_file_to_image(vars->init,"sprites_test/south.xpm", &(vars->nik.reso), &(vars->nik.reso2));
	printf("%d\t%d\n", vars->nik.reso, vars->nik.reso2);
	vars->nik.data = (unsigned int *)mlx_get_data_addr(vars->nik.image, &bpp, &sizeline, &endian);
//	mlx_put_image_to_window(vars->mlx, vars->win, vars->nik.image, 400, 0);
	mlx_loop_hook(vars->init, toto, &vars);
	toto(&vars);
	mlx_loop(vars->init);
	return (0);
}

