/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:29:26 by Bastian           #+#    #+#             */
/*   Updated: 2020/07/11 16:31:47 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
