/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:04:36 by Bastian           #+#    #+#             */
/*   Updated: 2020/07/11 16:53:57 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		ft_wall(t_mlx **mlx)
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

void		ft_wall_2(t_mlx **mlx)
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
	(*mlx)->image.text_x = (int)(((*mlx)->image.wall_x *
				((double)(*mlx)->image.width)));
	if ((*mlx)->space.side == 0 && (*mlx)->vect.raydir_x > 0)
		(*mlx)->image.text_x = (*mlx)->image.width - (*mlx)->image.text_x - 1;
	if ((*mlx)->space.side == 1 && (*mlx)->vect.raydir_y < 0)
		(*mlx)->image.text_x = (*mlx)->image.width - (*mlx)->image.text_x - 1;
	(*mlx)->image.step = 1.0 * (*mlx)->image.height / (*mlx)->draw.line_height;
	(*mlx)->image.text_pos = ((*mlx)->draw.draw_start - (*mlx)->cub.r[1] / 2
			+ (*mlx)->draw.line_height / 2) * (*mlx)->image.step;
}

static void	ft_text_south_north(t_mlx **mlx)
{
	if (((((*mlx)->space.old_wall_dist - (*mlx)->space.wall_dist) > 0.000001
		&& (*mlx)->vect.dir_y < 0) || (((*mlx)->space.wall_dist
		- (*mlx)->space.old_wall_dist) > 0.000001 &&
		(*mlx)->vect.dir_y > 0)) || ft_comp_float((*mlx)->vect.dir_x, -1.0))
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

static void	ft_text_west_east(t_mlx **mlx)
{
	if (((((*mlx)->space.old_wall_dist - (*mlx)->space.wall_dist) > 0.000001
		&& (*mlx)->vect.dir_x < 0) || (((*mlx)->space.wall_dist
		- (*mlx)->space.old_wall_dist) > 0.000001 &&
		(*mlx)->vect.dir_x > 0)) || ft_comp_float((*mlx)->vect.dir_y, -1))
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

void		ft_wall_text(t_mlx **mlx)
{
	if (ft_comp_float((*mlx)->space.side, 0))
		ft_text_south_north(mlx);
	else if (ft_comp_float((*mlx)->space.side, 1))
		ft_text_west_east(mlx);
	(*mlx)->space.old_wall_dist = (*mlx)->space.wall_dist;
}
