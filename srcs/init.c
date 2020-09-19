/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:57:10 by Bastian           #+#    #+#             */
/*   Updated: 2020/09/07 13:19:11 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_position(t_mlx *mlx)
{
	int position;

	position = ft_position_player(&(mlx->cub));
	if (position == 2)
	{
		mlx->vect.dir_x = 0;
		mlx->vect.dir_y = 1;
		mlx->vect.plane_x = 0.66;
		mlx->vect.plane_y = 0;
	}
	else if (position == 0)
	{
		mlx->vect.dir_x = 0;
		mlx->vect.dir_y = -1;
		mlx->vect.plane_x = -0.66;
		mlx->vect.plane_y = 0;
	}
	else if (position == 3)
	{
		mlx->vect.dir_x = 1;
		mlx->vect.dir_y = 0;
		mlx->vect.plane_x = 0;
		mlx->vect.plane_y = -0.66;
	}
	ft_position_sprite(&mlx);
}

void	ft_init_raycast(t_mlx **mlx)
{
	(*mlx)->space.hit = 0;
	(*mlx)->vect.camera_x = 2 * (*mlx)->count.i / (double)(*mlx)->cub.r[0] - 1;
	(*mlx)->vect.raydir_x = (*mlx)->vect.dir_x + (*mlx)->vect.plane_x *
		(*mlx)->vect.camera_x;
	(*mlx)->vect.raydir_y = (*mlx)->vect.dir_y + (*mlx)->vect.plane_y *
		(*mlx)->vect.camera_x;
	(*mlx)->space.map_x = (*mlx)->space.pos_x;
	(*mlx)->space.map_y = (*mlx)->space.pos_y;
	(*mlx)->vect.delta_dist_x = fabs(1 / (*mlx)->vect.raydir_x);
	(*mlx)->vect.delta_dist_y = fabs(1 / (*mlx)->vect.raydir_y);
}

void	ft_init_value(t_mlx *mlx)
{
	int x;
	int y;

	(mlx)->count.i = -1;
	mlx_get_screen_size(mlx->mlx_init, &x, &y);
	if (mlx->cub.r[0] >= x)
		mlx->cub.r[0] = x - 1;
	if (mlx->cub.r[1] >= y)
		mlx->cub.r[1] = y - 1;
	mlx->space.pos_x = ft_give_xy_map(&(mlx->cub), 1) + 0.5;
	mlx->space.pos_y = ft_give_xy_map(&(mlx->cub), 0) + 0.5;
	mlx->move.move_speed = 1;
	mlx->move.rot_speed = M_PI / 45;
	mlx->vect.dir_x = -1;
	mlx->vect.dir_y = 0;
	mlx->vect.plane_x = 0;
	mlx->vect.plane_y = 0.66;
	mlx->space.old_wall_dist = -1;
	mlx->sprite.specs = malloc(sizeof(int*) * (mlx)->cub.nb_sprites);
	while ((mlx)->count.i++ < (mlx)->cub.nb_sprites - 1)
		mlx->sprite.specs[(int)(mlx)->count.i] = malloc(sizeof(int) * 3);
}
