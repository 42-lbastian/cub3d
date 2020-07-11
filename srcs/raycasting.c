/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:39:26 by Bastian           #+#    #+#             */
/*   Updated: 2020/07/11 10:53:07 by Bastian          ###   ########.fr       */
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

static int ft_position_sprite(t_mlx **mlx)
{
	int i;
	int j;

	i = 0;
	j = 0;
	(*mlx)->sprite.nb = 0;
	while (i < ft_size_map((*mlx)->cub.size_map))
	{
		while (j < (*mlx)->cub.size_map[i])
		{
			if ((*mlx)->cub.map[i][j] == 2)
			{
				(*mlx)->sprite.specs[(*mlx)->sprite.nb][0] = i + 0.5;
				(*mlx)->sprite.specs[(*mlx)->sprite.nb][1] = j + 0.5;
				(*mlx)->sprite.specs[(*mlx)->sprite.nb][2] = (*mlx)->cub.map[i][j];

				(*mlx)->sprite.nb++;
			}
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
	int			rgb[3];

	(*mlx)->count.l = 0;
	while ((*mlx)->count.l++ < (*mlx)->draw.draw_start)
	{
		color = (*mlx)->cub.c;
		rgb[0] = (color & 0xff0000) >> 16;
		rgb[1] = (color & 0xff00) >> 8;
		rgb[2] = (color & 0xff);
		if (rgb[0] > ((*mlx)->count.l / 1.35) + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9)
			rgb[0] -= (((*mlx)->count.l / 1.35) + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
		else
			rgb[0] = 0;

		if (rgb[1] > ((*mlx)->count.l / 1.35) + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9)
			rgb[1] -= (((*mlx)->count.l / 1.35) + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
		else
			rgb[1] = 0;

		if (rgb[2] > ((*mlx)->count.l / 1.35) + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9)
			rgb[2] -= (((*mlx)->count.l / 1.35) + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
		else
			rgb[2] = 0;



		((*mlx)->image.data_rendering[(((*mlx)->count.l) * (*mlx)->cub.r[0]) + (int)(*mlx)->count.i]) =
			(rgb[0] << 16) +
			(rgb[1] << 8) +
			(rgb[2]);

	}
	(*mlx)->count.l--;
	while ((*mlx)->count.l++ < (*mlx)->draw.draw_end)
	{
		(*mlx)->image.text_y = (int)(*mlx)->image.text_pos;
		(*mlx)->image.text_pos += (*mlx)->image.step;
		color = (*mlx)->image.data_img[(*mlx)->image.height * (*mlx)->image.text_y + (*mlx)->image.text_x];
		rgb[0] = (color & 0xff0000) >> 16;
		rgb[1] = (color & 0xff00) >> 8;
		rgb[2] = (color & 0xff);

		if ((*mlx)->space.wall_dist > 2)
		{
			((*mlx)->image.data_rendering[((*mlx)->count.l * (*mlx)->cub.r[0]) + (int)(*mlx)->count.i]) =
				(((int)(rgb[0] / (((*mlx)->space.wall_dist / 2)))) << 16) +
				(((int)(rgb[1] / (((*mlx)->space.wall_dist / 2)))) << 8) +
				(((int)(rgb[2] / (((*mlx)->space.wall_dist / 2)))));
		}
		else
		{

			((*mlx)->image.data_rendering[((*mlx)->count.l * (*mlx)->cub.r[0]) + (int)(*mlx)->count.i]) =
				(rgb[0] << 16) +
				(rgb[1]  << 8) +
				(rgb[2]);
		}
	}
	(*mlx)->count.l--;
	while ((*mlx)->count.l++ < (*mlx)->cub.r[1])
	{
		color = (*mlx)->cub.f;
		rgb[0] = (color & 0xff0000) >> 16;
		rgb[1] = (color & 0xff00) >> 8;
		rgb[2] = (color & 0xff);
		if ((rgb[0] > (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9)))
			rgb[0] -= (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
		else
			rgb[0] = 0;

		if ((rgb[1] > (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9)))
			rgb[1] -= (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
		else
			rgb[1] = 0;

		if ((rgb[2] > (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9)))
			rgb[2] -= (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 + abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
		else
			rgb[2] = 0;

		((*mlx)->image.data_rendering[((*mlx)->count.l * (*mlx)->cub.r[0]) + (int)(*mlx)->count.i]) =
			(rgb[0] << 16) +
			(rgb[1] << 8) +
			(rgb[2]);
	}
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
	if (ft_comp_float((*mlx)->space.side, 0))
	{
		if (((((*mlx)->space.old_wall_dist - (*mlx)->space.wall_dist) > 0.000001 && (*mlx)->vect.dir_y < 0) || (((*mlx)->space.wall_dist - (*mlx)->space.old_wall_dist) > 0.000001 && (*mlx)->vect.dir_y > 0)) || ft_comp_float((*mlx)->vect.dir_x, -1.0))
		{
			(*mlx)->image.data_img = (unsigned int *)mlx_get_data_addr(
					(*mlx)->image.south, &(*mlx)->image.bpp, &(*mlx)->image.bordel,
					&(*mlx)->image.endian);
		}
		else
		{
			(*mlx)->image.data_img = (unsigned int *)mlx_get_data_addr(
					(*mlx)->image.north, &(*mlx)->image.bpp, &(*mlx)->image.bordel,
					&(*mlx)->image.endian);
		}
	}
	else if (ft_comp_float((*mlx)->space.side, 1))
	{
		if (((((*mlx)->space.old_wall_dist - (*mlx)->space.wall_dist) > 0.000001 && (*mlx)->vect.dir_x < 0) || (((*mlx)->space.wall_dist - (*mlx)->space.old_wall_dist) > 0.000001 && (*mlx)->vect.dir_x > 0)) || ft_comp_float((*mlx)->vect.dir_y, -1))
		{
			(*mlx)->image.data_img = (unsigned int *)mlx_get_data_addr(
					(*mlx)->image.west, &(*mlx)->image.bpp, &(*mlx)->image.bordel,
					&(*mlx)->image.endian);
		}
		else
		{
			(*mlx)->image.data_img = (unsigned int *)mlx_get_data_addr(
					(*mlx)->image.east, &(*mlx)->image.bpp, &(*mlx)->image.bordel,
					&(*mlx)->image.endian);
		}
	}

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

void	sort_sprites(int *order, double *dist, int nb)
{
	int temp_int;
	double temp_double;

	for (int i = 0; i < nb - 1; i++)
	{
		for (int j = 0; j < nb - i - 1; j++)
		{
			if (dist[j] < dist[j + 1])
			{
				temp_double = dist[j];
				temp_int = order[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = temp_double;
				order[j] = order[j + 1];
				order[j + 1] = temp_int;
			}
		}
	}
}

int		ft_raycast(t_mlx **mlx)
{
	(*mlx)->count.i = 0;
	double dist_buffer[(*mlx)->cub.r[0]];

	while((*mlx)->count.i < (*mlx)->cub.r[0])
	{
		ft_init_raycast(mlx);
		ft_direction(mlx);
		ft_obstacle_calculation(mlx);
		ft_draw_image(mlx);
		dist_buffer[(int)(*mlx)->count.i] = (*mlx)->space.wall_dist;
		(*mlx)->count.i++;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	ft_position_sprite(mlx);

	double sprite_x;
	double sprite_y;
	double inv_det;
	double transform_x;
	double transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
	int		rgb[3];

	(*mlx)->sprite.data_sp = (unsigned int *)mlx_get_data_addr((*mlx)->sprite.sprite, &(*mlx)->image.bordel, &(*mlx)->image.bordel, &(*mlx)->image.bordel);
	int sprite_order[(*mlx)->sprite.nb];
	double sprite_dist[(*mlx)->sprite.nb];

	for (int i = 0; i < (*mlx)->sprite.nb; i++)
	{
		sprite_order[i] = i;
		sprite_dist[i] = (((*mlx)->space.pos_x - (*mlx)->sprite.specs[i][0]) * ((*mlx)->space.pos_x - (*mlx)->sprite.specs[i][0]) + ((*mlx)->space.pos_y - (*mlx)->sprite.specs[i][1]) * ((*mlx)->space.pos_y - (*mlx)->sprite.specs[i][1]));
	}

	sort_sprites(sprite_order, sprite_dist, (*mlx)->sprite.nb);

	for (int i = 0; i < (*mlx)->sprite.nb; i++)
	{
		sprite_x = (*mlx)->sprite.specs[sprite_order[i]][0] - (*mlx)->space.pos_x;
		sprite_y = (*mlx)->sprite.specs[sprite_order[i]][1] - (*mlx)->space.pos_y;
		inv_det = 1.0 / ((*mlx)->vect.plane_x * (*mlx)->vect.dir_y - (*mlx)->vect.plane_y * (*mlx)->vect.dir_x);
		transform_x = inv_det * ((*mlx)->vect.dir_y * sprite_x - (*mlx)->vect.dir_x * sprite_y);
		transform_y = inv_det * (-(*mlx)->vect.plane_y * sprite_x + (*mlx)->vect.plane_x * sprite_y);
		sprite_screen_x = (int)(((*mlx)->cub.r[0] / 2) * (1 + transform_x / transform_y));

		sprite_height = abs((int)((*mlx)->cub.r[1] / transform_y));
		draw_start_y = -sprite_height / 2 + (*mlx)->cub.r[1] / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		draw_end_y = sprite_height / 2 + (*mlx)->cub.r[1] / 2;
		if (draw_end_y >= (*mlx)->cub.r[1])
			draw_end_y = (*mlx)->cub.r[1];

		sprite_width = abs((int)((*mlx)->cub.r[1] / transform_y));
		draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_start_x >= (*mlx)->cub.r[0])
			draw_start_x = (*mlx)->cub.r[0];
		for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			int tex_x = ((int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * (*mlx)->sprite.width / sprite_width)) / 256;
			if (transform_y > 0 && stripe > 0 && stripe < (*mlx)->cub.r[0] && transform_y < dist_buffer[stripe])
			{
				for (int y = draw_start_y; y < draw_end_y; y++)
				{
					int d = (y) * 256 - (*mlx)->cub.r[1] * 128 + sprite_height * 128;
					int tex_y = ((d * (*mlx)->sprite.height) / sprite_height) / 256;
					int color = (*mlx)->sprite.data_sp[(*mlx)->sprite.width * (tex_y) + tex_x];
					if (color)
					{
						rgb[0] = (color & 0xff0000) >> 16;
						rgb[1] = (color & 0xff00) >> 8;
						rgb[2] = (color & 0xff);
						if (sprite_dist[i] > 20)
							(*mlx)->image.data_rendering[y * (*mlx)->cub.r[0] + (stripe)] =
								(((int)(rgb[0] / ((sprite_dist[i]  / 20)))) << 16) +
								(((int)(rgb[1] / ((sprite_dist[i]  / 20)))) << 8) +
								(((int)(rgb[2] / ((sprite_dist[i]  / 20)))));
						else
							(*mlx)->image.data_rendering[y * (*mlx)->cub.r[0] + (stripe)] = color;
					}
				}
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////


	mlx_put_image_to_window((*mlx)->mlx_init, (*mlx)->mlx_screen,
			(*mlx)->image.img_rendering, 0, 0);
	return (1);
}

int             ft_key_2(int keycode, t_mlx **mlx)
{
	if (keycode == 100) //D
	{
		if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x + (*mlx)->vect.dir_y *
						(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] == 0)
			(*mlx)->space.pos_x += (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
		if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x )][((int)((*mlx)->space.pos_y -
						(*mlx)->vect.dir_x * (*mlx)->move.move_speed))] == 0)
			(*mlx)->space.pos_y -= (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	}
	if (keycode == 97 || keycode == 113) //A
	{
		if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x - (*mlx)->vect.dir_y *
						(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] == 0)
			(*mlx)->space.pos_x -= (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
		if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x )][((int)((*mlx)->space.pos_y
						+ (*mlx)->vect.dir_x * (*mlx)->move.move_speed))] == 0)
			(*mlx)->space.pos_y += (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	}
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
					(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] == 0)
		(*mlx)->space.pos_x += (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x )][((int)((*mlx)->space.pos_y
					+ (*mlx)->vect.dir_y * (*mlx)->move.move_speed))] == 0)
		(*mlx)->space.pos_y += (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
}

void	ft_backward(t_mlx **mlx)
{
	if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x - (*mlx)->vect.dir_x *
					(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] == 0)
		(*mlx)->space.pos_x -= (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x )][((int)((*mlx)->space.pos_y
					- (*mlx)->vect.dir_y * (*mlx)->move.move_speed))] == 0)
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
	mlx->sprite.specs = malloc(sizeof(int*) * 2);
	for (int i = 0; i < 2; i++)
		mlx->sprite.specs[i] = malloc(sizeof(int) * 3);
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
