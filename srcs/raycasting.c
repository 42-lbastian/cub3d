/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:39:26 by Bastian           #+#    #+#             */
/*   Updated: 2020/07/04 15:51:39 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


static int ft_give_xy_map(t_cub *cub, int fact)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < ft_size_map(cub->size_map))
	{
		while (j < cub->size_map[i])
		{
			if (cub->map[i][j] > 20)
			{
				if (fact == 1)
					return (i);
				else
					return (j);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

static int ft_position_player(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < ft_size_map(cub->size_map))
	{
		while (j < cub->size_map[i])
		{
			if (cub->map[i][j] == 30)
				return (1);
			if (cub->map[i][j] == 39)
				return (0);
			if (cub->map[i][j] == 35)
				return (3);
			if (cub->map[i][j] == 21)
				return (2);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

void	ft_draw_image(t_mlx **mlx)
{
	unsigned int color;
	(*mlx)->count.l = (*mlx)->draw.draw_start - 1;
//	while ((*mlx)->count.l++ < (*mlx)->draw.draw_start - 1 - (*mlx)->move.crouch)
//		(*mlx)->image.data_rendering[((*mlx)->count.l * (*mlx)->cub.r[0]) +
//			(int)(*mlx)->count.i] = mlx_get_color_value((*mlx)->mlx_init, (*mlx)->cub.c);
//	(*mlx)->count.l--;
	while ((*mlx)->count.l++ < (*mlx)->draw.draw_end - (*mlx)->move.crouch)
	{
		(*mlx)->image.text_y = (int)(*mlx)->image.text_pos;
		(*mlx)->image.text_pos += (*mlx)->image.step;
//		color = mlx_get_color_value((*mlx)->mlx_init, (*mlx)->image.data_img[(*mlx)->image.height * (*mlx)->image.text_y + (*mlx)->image.text_x]);
		color = mlx_get_color_value((*mlx)->mlx_init, (255 << 16) + (0 << 8) + 0);
		((*mlx)->image.data_rendering[((*mlx)->count.l * (*mlx)->cub.r[0]) + (int)(*mlx)->count.i]) = color;
	}
//	(*mlx)->count.l -= 2;
//	while ((*mlx)->count.l++ < (*mlx)->cub.r[1])
//		(*mlx)->image.data_rendering[((*mlx)->count.l * (*mlx)->cub.r[0]) +
//			(int)(*mlx)->count.i] = mlx_get_color_value((*mlx)->mlx_init, (*mlx)->cub.f);

}

void	ft_direction(t_mlx **mlx)
{
	if ((*mlx)->vect.raydir_x < 0)
	{
		(*mlx)->space.step_x = -1;
		(*mlx)->vect.side_dist_x = ((*mlx)->space.pos_x -
				(*mlx)->space.map_x) * (*mlx)->vect.delta_dist_x;
	}
	else
	{
		(*mlx)->space.step_x = 1;
		(*mlx)->vect.side_dist_x = ((*mlx)->space.map_x + 1.0 -
				(*mlx)->space.pos_x) * (*mlx)->vect.delta_dist_x;
	}
	if ((*mlx)->vect.raydir_y < 0)
	{
		(*mlx)->space.step_y = -1;
		(*mlx)->vect.side_dist_y = ((*mlx)->space.pos_y -
				(*mlx)->space.map_y) * (*mlx)->vect.delta_dist_y;
	}
	else
	{
		(*mlx)->space.step_y = 1;
		(*mlx)->vect.side_dist_y = ((*mlx)->space.map_y + 1.0 -
				(*mlx)->space.pos_y) * (*mlx)->vect.delta_dist_y;
	}
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

void	ft_wall_text(t_mlx **mlx)
{
	/*		if (ft_comp_float((*mlx)->space.side, 0))
			{
			if (((((*mlx)->space.old_wall_dist - (*mlx)->space.wall_dist) > 0.000001 && (*mlx)->vect.dir_y < 0) || (((*mlx)->space.wall_dist - (*mlx)->space.old_wall_dist) > 0.000001 && (*mlx)->vect.dir_y > 0)) || (*mlx)->vect.dir_x < -0.5)
			(*mlx)->draw.color = mlx_get_color_value((*mlx)->mlx_init, (0 << 16) + (0 << 8) + 0);
			else
			(*mlx)->draw.color = mlx_get_color_value((*mlx)->mlx_init, (255 << 16) + (0 << 8) + 0);
			}
			else if (ft_comp_float((*mlx)->space.side, 1))
			{
			if (((((*mlx)->space.old_wall_dist - (*mlx)->space.wall_dist) > 0.000001 && (*mlx)->vect.dir_x < 0) || (((*mlx)->space.wall_dist - (*mlx)->space.old_wall_dist) > 0.000001 && (*mlx)->vect.dir_x > 0)) || (*mlx)->vect.dir_y < -0.5)
			(*mlx)->draw.color = mlx_get_color_value((*mlx)->mlx_init, (0 << 16) + (0 << 8) + 255);
			else
			(*mlx)->draw.color = mlx_get_color_value((*mlx)->mlx_init, (0 << 16) + (255 << 8) + 0);
			}
	 */
	if (ft_comp_float((*mlx)->space.side, 0))
		(*mlx)->image.data_img = (unsigned int *)mlx_get_data_addr(
			(*mlx)->image.north, &(*mlx)->image.bordel, &(*mlx)->image.bordel,
				&(*mlx)->image.bordel);
	else if (ft_comp_float((*mlx)->space.side, 1))
		(*mlx)->image.data_img = (unsigned int *)mlx_get_data_addr(
			(*mlx)->image.east, &(*mlx)->image.bordel, &(*mlx)->image.bordel,
				&(*mlx)->image.bordel);
	(*mlx)->space.old_wall_dist = (*mlx)->space.wall_dist;

}

void	ft_wall_2(t_mlx **mlx)
{
	if ((*mlx)->draw.draw_end >= (*mlx)->cub.r[1])
		(*mlx)->draw.draw_end = (*mlx)->cub.r[1] - 1;
	if ((*mlx)->space.side == 0)
		(*mlx)->image.wall_x = (*mlx)->space.pos_y + (*mlx)->space.wall_dist
			* (*mlx)->vect.raydir_y;
	else
		(*mlx)->image.wall_x = (*mlx)->space.pos_x + (*mlx)->space.wall_dist
			* (*mlx)->vect.raydir_x;
	(*mlx)->image.wall_x -= floor(((*mlx)->image.wall_x));
	(*mlx)->image.text_x = (int)(((*mlx)->image.wall_x * ((double)(*mlx)->image.width)));
	if((*mlx)->space.side == 0 && (*mlx)->vect.raydir_x > 0)
		(*mlx)->image.text_x = (*mlx)->image.width - (*mlx)->image.text_x - 1;
	if((*mlx)->space.side == 1 && (*mlx)->vect.raydir_y < 0)
		(*mlx)->image.text_x = (*mlx)->image.width - (*mlx)->image.text_x - 1;
	(*mlx)->image.step = 1.0 * (*mlx)->image.height / (*mlx)->draw.line_height;
	(*mlx)->image.text_pos = ((*mlx)->draw.draw_start - (*mlx)->cub.r[1]  / 2
			+ (*mlx)->draw.line_height / 2) * (*mlx)->image.step;
}

void	ft_wall(t_mlx **mlx)
{
	(*mlx)->space.hit = 1;
	if ((*mlx)->space.side == 0 && (*mlx)->vect.raydir_x != 0)
		(*mlx)->space.wall_dist = ((*mlx)->space.map_x - (*mlx)->space.pos_x
				+ (1 - (*mlx)->space.step_x) / 2) / (*mlx)->vect.raydir_x;
	else if ((*mlx)->space.side != 0 && (*mlx)->vect.raydir_y != 0)
		(*mlx)->space.wall_dist = ((*mlx)->space.map_y - (*mlx)->space.pos_y
				+ (1 - (*mlx)->space.step_y) / 2) / (*mlx)->vect.raydir_y;
	if ((*mlx)->space.wall_dist != 0)
		(*mlx)->draw.line_height = (*mlx)->cub.r[1] / (*mlx)->space.wall_dist;
	else
		(*mlx)->draw.line_height = (*mlx)->cub.r[1];
	(*mlx)->draw.draw_start = (-(*mlx)->draw.line_height / 2) +
		((*mlx)->cub.r[1] / 2);
	if ((*mlx)->draw.draw_start < 0)
		(*mlx)->draw.draw_start = 0;
	(*mlx)->draw.draw_end = (*mlx)->draw.line_height / 2 +
		(*mlx)->cub.r[1] / 2;
	ft_wall_2(mlx);
	ft_wall_text(mlx);
}

void	ft_obstacle_calculation(t_mlx **mlx)
{
	while ((*mlx)->space.hit == 0)
	{
		if ((*mlx)->vect.side_dist_x < (*mlx)->vect.side_dist_y)
		{
			(*mlx)->vect.side_dist_x += (*mlx)->vect.delta_dist_x;
			(*mlx)->space.map_x += (*mlx)->space.step_x;
			(*mlx)->space.side = 0;
		}
		else
		{
			(*mlx)->vect.side_dist_y += (*mlx)->vect.delta_dist_y;
			(*mlx)->space.map_y += (*mlx)->space.step_y;
			(*mlx)->space.side = 1;
		}
		if ((*mlx)->cub.map[(*mlx)->space.map_x][(*mlx)->space.map_y] == 1)
			ft_wall(mlx);
	}
}

int		ft_raycast(t_mlx **mlx)
{
	int i = 0;
	(*mlx)->count.i = 0;
	unsigned int *data_sp = (unsigned int *)mlx_get_data_addr((*mlx)->image.south, &(*mlx)->image.bordel, &(*mlx)->image.bordel, &(*mlx)->image.bordel);

	while (i < (*mlx)->cub.r[1])
	{
		float ray_dir_x0 = (*mlx)->vect.dir_x - (*mlx)->vect.plane_x;
		float ray_dir_y0 = (*mlx)->vect.dir_y - (*mlx)->vect.plane_y;
		float ray_dir_x1 = (*mlx)->vect.dir_x + (*mlx)->vect.plane_x;
		float ray_dir_y1 = (*mlx)->vect.dir_y + (*mlx)->vect.plane_y;
		int p = i - (*mlx)->cub.r[1] / 2;
		float pos_z = 0.5 * (*mlx)->cub.r[1];
		float row_distance = pos_z / p;
		float floorstep_x = row_distance * (ray_dir_x1 - ray_dir_x0) / (*mlx)->cub.r[0];
		float floorstep_y = row_distance * (ray_dir_y1 - ray_dir_y0) / (*mlx)->cub.r[0];
		float floor_x = (*mlx)->space.pos_x + row_distance * ray_dir_x0;
		float floor_y = (*mlx)->space.pos_y + row_distance * ray_dir_y0;

		for (int l = 0; l < (*mlx)->cub.r[0]; l++)
		{
			int tx = (int)(500 * (floor_x - ((int)floor_x))) & (500 - 1);
			int ty = (int)(500 * (floor_y - ((int)floor_y))) & (500 - 1);

			floor_x += floorstep_x;
			floor_y += floorstep_y;

			//printf("tx:%d\tty:%d\ti:%d\tl:%d\n", tx, ty, i, l);
			(*mlx)->image.data_rendering[(i * (*mlx)->cub.r[0]) + l] = data_sp[500 * ty + tx];
		}
		i++;
	}
	(*mlx)->count.i = 0;
	while((*mlx)->count.i < (*mlx)->cub.r[0])
	{
		ft_init_raycast(mlx);
		ft_direction(mlx);
		ft_obstacle_calculation(mlx);
		ft_draw_image(mlx);
		(*mlx)->count.i++;
	}
	mlx_put_image_to_window((*mlx)->mlx_init, (*mlx)->mlx_screen,
			(*mlx)->image.img_rendering, 0, 0);
	return (1);
}

int             ft_key_2(int keycode, t_mlx **mlx)
{
	if (keycode == 100) //D
	{
		if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x + (*mlx)->vect.dir_y *
						(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] != 1)
			(*mlx)->space.pos_x += (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
		if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x )][((int)((*mlx)->space.pos_y -
						(*mlx)->vect.dir_x * (*mlx)->move.move_speed))] != 1)
			(*mlx)->space.pos_y -= (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	}
	if (keycode == 97 || keycode == 113) //A
	{
		if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x - (*mlx)->vect.dir_y *
						(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] != 1)
			(*mlx)->space.pos_x -= (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
		if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x )][((int)((*mlx)->space.pos_y
						+ (*mlx)->vect.dir_x * (*mlx)->move.move_speed))] != 1)
			(*mlx)->space.pos_y += (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	}
	if (keycode == 65505)
		(*mlx)->move.crouch = 0;
	return (1);
}

int             ft_close(t_mlx **mlx)
{
	mlx_destroy_window((*mlx)->mlx_init, (*mlx)->mlx_screen);
	exit(0);
	return (1);
}


void	ft_forward(t_mlx **mlx)
{
	if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x + (*mlx)->vect.dir_x *
					(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] != 1)
		(*mlx)->space.pos_x += (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x )][((int)((*mlx)->space.pos_y
					+ (*mlx)->vect.dir_y * (*mlx)->move.move_speed))] != 1)
		(*mlx)->space.pos_y += (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
}

void	ft_backward(t_mlx **mlx)
{
	if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x - (*mlx)->vect.dir_x *
					(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] != 1)
		(*mlx)->space.pos_x -= (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x )][((int)((*mlx)->space.pos_y
					- (*mlx)->vect.dir_y * (*mlx)->move.move_speed))] != 1)
		(*mlx)->space.pos_y -= (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
}

void	ft_turn_right(t_mlx **mlx)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = (*mlx)->vect.dir_x;
	old_plane_x = (*mlx)->vect.plane_x;
	(*mlx)->vect.dir_x = (*mlx)->vect.dir_x * cos(-(*mlx)->move.rot_speed)
		- (*mlx)->vect.dir_y * sin(-(*mlx)->move.rot_speed);
	(*mlx)->vect.dir_y = old_dir_x * sin(-(*mlx)->move.rot_speed) +
		(*mlx)->vect.dir_y * cos(-(*mlx)->move.rot_speed);
	(*mlx)->vect.plane_x = (*mlx)->vect.plane_x * cos(-(*mlx)->move.rot_speed)
		- (*mlx)->vect.plane_y * sin(-(*mlx)->move.rot_speed);
	(*mlx)->vect.plane_y = old_plane_x * sin(-(*mlx)->move.rot_speed)
		+ (*mlx)->vect.plane_y * cos(-(*mlx)->move.rot_speed);
}

void	ft_turn_left(t_mlx **mlx)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = (*mlx)->vect.dir_x;
	old_plane_x = (*mlx)->vect.plane_x;
	(*mlx)->vect.dir_x = (*mlx)->vect.dir_x * cos((*mlx)->move.rot_speed)
		- (*mlx)->vect.dir_y * sin((*mlx)->move.rot_speed);
	(*mlx)->vect.dir_y = old_dir_x * sin((*mlx)->move.rot_speed) +
		(*mlx)->vect.dir_y * cos((*mlx)->move.rot_speed);
	(*mlx)->vect.plane_x = (*mlx)->vect.plane_x * cos((*mlx)->move.rot_speed)
		- (*mlx)->vect.plane_y * sin((*mlx)->move.rot_speed);
	(*mlx)->vect.plane_y = old_plane_x * sin((*mlx)->move.rot_speed) +
		(*mlx)->vect.plane_y * cos((*mlx)->move.rot_speed);

}

int             ft_key_1(int keycode, t_mlx **mlx)
{


	if (keycode == 65307)
	{
		mlx_destroy_window((*mlx)->mlx_init, (*mlx)->mlx_screen);
		exit(0);
	}
	if (keycode == 119 || keycode == 122)
		ft_forward(mlx);
	if (keycode == 115)
		ft_backward(mlx);
	if (keycode == 65363)
		ft_turn_right(mlx);
	if (keycode == 65361)
		ft_turn_left(mlx);
	if (keycode == 65505)
		(*mlx)->move.crouch = (*mlx)->cub.r[0] / 25;
	return (1);
}

void	ft_init_value(t_mlx *mlx)
{
	int x;
	int y;

	mlx_get_screen_size(mlx->mlx_init, &x, &y);
	if (mlx->cub.r[0] > x)
		mlx->cub.r[0] = x;
	if (mlx->cub.r[1] > y)
		mlx->cub.r[1] = y;
	mlx->space.pos_x = ft_give_xy_map(&(mlx->cub), 1) + 0.5;
	mlx->space.pos_y = ft_give_xy_map(&(mlx->cub), 0) + 0.5;
	mlx->move.move_speed = 1;
	mlx->move.rot_speed =  M_PI / 45;
	mlx->vect.dir_x = -1;
	mlx->vect.dir_y = 0;
	mlx->vect.plane_x = 0;
	mlx->vect.plane_y = 0.66;
	mlx->space.old_wall_dist = -1;
}

void	ft_init_position(t_mlx *mlx)
{
	if (ft_position_player(&(mlx->cub)) == 2)
	{
		mlx->vect.dir_x = 0;
		mlx->vect.dir_y = 1;
		mlx->vect.plane_x = 0.66;
		mlx->vect.plane_y = 0;
	}
	else if (ft_position_player(&(mlx->cub)) == 0)
	{
		mlx->vect.dir_x = 0;
		mlx->vect.dir_y = -1;
		mlx->vect.plane_x = -0.66;
		mlx->vect.plane_y = 0;
	}
	else if (ft_position_player(&(mlx->cub)) == 3)
	{
		mlx->vect.dir_x = 1;
		mlx->vect.dir_y = 0;
		mlx->vect.plane_x = 0;
		mlx->vect.plane_y = -0.66;
	}
}

int ft_raycast_launch(t_mlx *mlx)
{
	ft_init_value(mlx);
	ft_init_position(mlx);
	mlx->mlx_screen = mlx_new_window(mlx->mlx_init, mlx->cub.r[0],
			mlx->cub.r[1], "Cub3D");
	mlx->image.img_rendering = mlx_new_image (mlx->mlx_init, mlx->cub.r[0],
			mlx->cub.r[1]);
	mlx->image.data_rendering = (unsigned int*)mlx_get_data_addr(
			mlx->image.img_rendering, &(mlx)->image.bordel, &(mlx)->image.bordel,
			&(mlx)->image.bordel);
	mlx_hook(mlx->mlx_screen, 3, 1L<<1, ft_key_2, &mlx);

	mlx_hook(mlx->mlx_screen, 2, 1L<<0, ft_key_1, &mlx);
	mlx_hook(mlx->mlx_screen, 17, 1L<<17, ft_close, &mlx);
	mlx_loop_hook(mlx->mlx_init, ft_raycast, &mlx);
	mlx_loop(mlx->mlx_init);
	return (0);
}
