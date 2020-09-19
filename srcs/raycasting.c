/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:39:26 by Bastian           #+#    #+#             */
/*   Updated: 2020/09/15 18:58:53 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			ft_raycast(t_mlx **mlx)
{
	double dist_buffer[(*mlx)->cub.r[0]];

	(*mlx)->count.i = 0;
	while ((*mlx)->count.i < (*mlx)->cub.r[0])
	{
		ft_init_raycast(mlx);
		ft_direction(mlx);
		ft_obstacle_calculation(mlx);
		ft_draw_image(mlx);
		dist_buffer[(int)(*mlx)->count.i] = (*mlx)->space.wall_dist;
		(*mlx)->count.i++;
	}
	ft_sprite(mlx, dist_buffer, -1, -1);
	mlx_put_image_to_window((*mlx)->mlx_init, (*mlx)->mlx_screen,
			(*mlx)->image.img_rendering, 0, 0);
	if ((*mlx)->cub.save == 1)
		ft_magic_bmp(mlx);
	return (1);
}

int			ft_key_2(int keycode, t_mlx **mlx)
{
	if (keycode == 100)
	{
		if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x + (*mlx)->vect.dir_y *
				(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] == 0)
			(*mlx)->space.pos_x += (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
		if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x)]
				[((int)((*mlx)->space.pos_y
				- (*mlx)->vect.dir_x * (*mlx)->move.move_speed))] == 0)
			(*mlx)->space.pos_y -= (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	}
	if (keycode == 97 || keycode == 113)
	{
		if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x - (*mlx)->vect.dir_y *
				(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] == 0)
			(*mlx)->space.pos_x -= (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
		if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x)]
				[((int)((*mlx)->space.pos_y
				+ (*mlx)->vect.dir_x * (*mlx)->move.move_speed))] == 0)
			(*mlx)->space.pos_y += (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	}
	return (1);
}

int			ft_close(t_mlx **mlx)
{
	ft_free_all(mlx);
	return (1);
}

int			ft_key_1(int keycode, t_mlx **mlx)
{
	if (keycode == 65307)
	{
		mlx_destroy_window((*mlx)->mlx_init, (*mlx)->mlx_screen);
		ft_free_all(mlx);
	}
	if (keycode == 119 || keycode == 122)
		ft_forward(mlx);
	if (keycode == 115)
		ft_backward(mlx);
	if (keycode == 65363)
		ft_turn_right(mlx);
	if (keycode == 65361)
		ft_turn_left(mlx);
	return (1);
}

int			ft_raycast_launch(t_mlx *mlx)
{
	int endian;

	ft_init_value(mlx);
	ft_init_position(mlx);
	mlx->mlx_screen = mlx_new_window(mlx->mlx_init, mlx->cub.r[0],
			mlx->cub.r[1], "Cub3D");
	mlx->image.img_rendering = mlx_new_image(mlx->mlx_init, mlx->cub.r[0],
			mlx->cub.r[1]);
	mlx->image.data_rendering = (unsigned int*)mlx_get_data_addr(
			mlx->image.img_rendering, &endian,
			&(mlx)->image.bordel, &(mlx)->image.bordel);
	mlx_hook(mlx->mlx_screen, 3, 1L << 1, ft_key_2, &mlx);
	mlx_hook(mlx->mlx_screen, 2, 1L << 0, ft_key_1, &mlx);
	mlx_hook(mlx->mlx_screen, 17, 1L << 17, ft_close, &mlx);
	mlx_loop_hook(mlx->mlx_init, ft_raycast, &mlx);
	mlx_loop(mlx->mlx_init);
	return (0);
}
