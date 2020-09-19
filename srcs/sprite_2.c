/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:32:34 by Bastian           #+#    #+#             */
/*   Updated: 2020/09/15 18:40:33 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_calc_sprite_2(t_mlx **mlx)
{
	(*mlx)->sprite.tex_x = ((int)(256 * ((*mlx)->count.stripe -
	(-(*mlx)->sprite.sprite_width / 2 + (*mlx)->sprite.screen_x)) *
	(*mlx)->sprite.width / (*mlx)->sprite.sprite_width)) / 256;
}

void	ft_sprite_draw(t_mlx **mlx, int y,
		double sprite_dist[(*mlx)->sprite.nb], int i)
{
	int				rgb[3];
	unsigned int	color;

	(*mlx)->sprite.d = (y) * 256 - (*mlx)->cub.r[1] * 128 +
		(*mlx)->sprite.sprite_height * 128;
	(*mlx)->sprite.tex_y = (((*mlx)->sprite.d *
				(*mlx)->sprite.height) /
			(*mlx)->sprite.sprite_height) / 256;
	color = (*mlx)->sprite.data_sp[(*mlx)->sprite.width *
		((*mlx)->sprite.tex_y) + (*mlx)->sprite.tex_x];
	if (color)
	{
		rgb[0] = (color & 0xff0000) >> 16;
		rgb[1] = (color & 0xff00) >> 8;
		rgb[2] = (color & 0xff);
		if (sprite_dist[i] > 20)
			(*mlx)->image.data_rendering[y * (*mlx)->cub.r[0]
				+ ((*mlx)->count.stripe)] =
				(((int)(rgb[0] / ((sprite_dist[i] / 20)))) << 16) +
				(((int)(rgb[1] / ((sprite_dist[i] / 20)))) << 8) +
				(((int)(rgb[2] / ((sprite_dist[i] / 20)))));
		else
			(*mlx)->image.data_rendering[y *
				(*mlx)->cub.r[0] + ((*mlx)->count.stripe)] = color;
	}
}
