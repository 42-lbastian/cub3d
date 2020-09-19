/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:54:09 by Bastian           #+#    #+#             */
/*   Updated: 2020/07/11 16:43:07 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_forward(t_mlx **mlx)
{
	if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x + (*mlx)->vect.dir_x *
			(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] == 0)
		(*mlx)->space.pos_x += (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x)][((int)((*mlx)->space.pos_y
					+ (*mlx)->vect.dir_y * (*mlx)->move.move_speed))] == 0)
		(*mlx)->space.pos_y += (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
}

void	ft_backward(t_mlx **mlx)
{
	if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x - (*mlx)->vect.dir_x *
			(*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] == 0)
		(*mlx)->space.pos_x -= (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
	if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x)][((int)((*mlx)->space.pos_y
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
