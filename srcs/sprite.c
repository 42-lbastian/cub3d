/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:25:34 by Bastian           #+#    #+#             */
/*   Updated: 2020/09/15 18:40:12 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sort_sprites(int *order, double *dist, int nb)
{
	int		temp_int;
	double	temp_double;
	int		i;
	int		j;

	i = -1;
	while (i++ < nb - 1)
	{
		j = -1;
		while (j++ < nb - i - 1)
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

void	ft_sprite_order(t_mlx **mlx, int i,
	double sprite_dist[(*mlx)->sprite.nb], int sprite_order[(*mlx)->sprite.nb])
{
	while (i < (*mlx)->sprite.nb)
	{
		sprite_order[i] = i;
		sprite_dist[i] = (((*mlx)->space.pos_x - (*mlx)->sprite.specs[i][0]) *
				((*mlx)->space.pos_x - (*mlx)->sprite.specs[i][0]) +
				((*mlx)->space.pos_y - (*mlx)->sprite.specs[i][1]) *
				((*mlx)->space.pos_y - (*mlx)->sprite.specs[i][1]));
		i++;
	}
	sort_sprites(sprite_order, sprite_dist, (*mlx)->sprite.nb);
	(*mlx)->sprite.data_sp = (unsigned int *)mlx_get_data_addr(
			(*mlx)->sprite.sprite, &(*mlx)->image.bordel,
			&(*mlx)->image.bordel, &(*mlx)->image.bordel);
}

void	ft_sprite_calc_coord(t_mlx **mlx, int i,
			int sprite_order[(*mlx)->sprite.nb])
{
	(*mlx)->sprite.x = (*mlx)->sprite.specs[sprite_order[i]][0] + 0.5 -
		(*mlx)->space.pos_x;
	(*mlx)->sprite.y = (*mlx)->sprite.specs[sprite_order[i]][1] + 0.5 -
		(*mlx)->space.pos_y;
	(*mlx)->sprite.inv_det = 1.0 / ((*mlx)->vect.plane_x *
			(*mlx)->vect.dir_y - (*mlx)->vect.plane_y * (*mlx)->vect.dir_x);
	(*mlx)->sprite.transform_x = (*mlx)->sprite.inv_det *
		((*mlx)->vect.dir_y * (*mlx)->sprite.x - (*mlx)->vect.dir_x
		* (*mlx)->sprite.y);
	(*mlx)->sprite.transform_y = (*mlx)->sprite.inv_det *
		(-(*mlx)->vect.plane_y *
		(*mlx)->sprite.x + (*mlx)->vect.plane_x * (*mlx)->sprite.y);
	(*mlx)->sprite.screen_x = (int)(((*mlx)->cub.r[0] / 2) *
			(1 + (*mlx)->sprite.transform_x / (*mlx)->sprite.transform_y));
	(*mlx)->sprite.sprite_height = abs((int)((*mlx)->cub.r[1] /
				(*mlx)->sprite.transform_y));
	(*mlx)->sprite.draw_start_y = -(*mlx)->sprite.sprite_height / 2
		+ (*mlx)->cub.r[1] / 2;
}

void	ft_sprite_calc_draw(t_mlx **mlx)
{
	if ((*mlx)->sprite.draw_start_y < 0)
		(*mlx)->sprite.draw_start_y = 0;
	(*mlx)->sprite.draw_end_y = (*mlx)->sprite.sprite_height / 2
		+ (*mlx)->cub.r[1] / 2;
	if ((*mlx)->sprite.draw_end_y >= (*mlx)->cub.r[1])
		(*mlx)->sprite.draw_end_y = (*mlx)->cub.r[1];
	if (ft_comp_float((*mlx)->sprite.transform_y, 0))
		(*mlx)->sprite.sprite_width = (int)((*mlx)->cub.r[1]);
	else
		(*mlx)->sprite.sprite_width = abs((int)((*mlx)->cub.r[1] /
				(*mlx)->sprite.transform_y));
	(*mlx)->sprite.draw_start_x = -(*mlx)->sprite.sprite_width / 2
		+ (*mlx)->sprite.screen_x;
	if ((*mlx)->sprite.draw_start_x < 0)
		(*mlx)->sprite.draw_start_x = 0;
	(*mlx)->sprite.draw_end_x = (*mlx)->sprite.sprite_width / 2
		+ (*mlx)->sprite.screen_x;
	if ((*mlx)->sprite.draw_start_x >= (*mlx)->cub.r[0])
		(*mlx)->sprite.draw_start_x = (*mlx)->cub.r[0];
}

void	ft_sprite(t_mlx **mlx, double dist_buffer[(*mlx)->cub.r[0]],
		int i, int y)
{
	int				sprite_order[(*mlx)->sprite.nb];
	double			sprite_dist[(*mlx)->sprite.nb];

	ft_sprite_order(mlx, 0, sprite_dist, sprite_order);
	while (i++ < (*mlx)->sprite.nb - 1)
	{
		ft_sprite_calc_coord(mlx, i, sprite_order);
		ft_sprite_calc_draw(mlx);
		(*mlx)->count.stripe = (*mlx)->sprite.draw_start_x - 1;
		while ((*mlx)->count.stripe++ < (*mlx)->sprite.draw_end_x - 1)
		{
			ft_calc_sprite_2(mlx);
			if ((*mlx)->sprite.transform_y > 0 && (*mlx)->count.stripe > 0 &&
					(*mlx)->count.stripe < (*mlx)->cub.r[0]
					&& (*mlx)->sprite.transform_y <
					dist_buffer[(*mlx)->count.stripe])
			{
				y = (*mlx)->sprite.draw_start_y - 1;
				while (y++ < (*mlx)->sprite.draw_end_y - 1)
					ft_sprite_draw(mlx, y, sprite_dist, i);
			}
		}
	}
}
