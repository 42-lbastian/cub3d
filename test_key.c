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
	int toto = 0;
	int rvb[3] = {0,0,0};

	unsigned  int color = mlx_get_color_value((*vars)->init, (1 << 16) + (254 << 8) + 4);
/*	for (int z = 31; z>= 0; z--)
	{
		if (color & (1u << z))
			printf("1-%d\n", z);
		else
			printf("0-%d\n", z);
	}
*/
	for (int z = 0; z <= 23; z++)
	{
		if (1u << z & color)
			rvb[(z) / 8] += pow(2, z % 8);
	}
	printf("%d-%d-%d\n", rvb[0], rvb[1], rvb[2]);
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
	vars->nik.image = mlx_xpm_file_to_image(vars->init,"text/north.xpm", &(vars->nik.reso), &(vars->nik.reso2));
	printf("%d\t%d\n", vars->nik.reso, vars->nik.reso2);
	vars->nik.data = (unsigned int *)mlx_get_data_addr(vars->nik.image, &bpp, &sizeline, &endian);
	mlx_loop_hook(vars->init, toto, &vars);
	toto(&vars);
	mlx_loop(vars->init);
	return (0);
}

