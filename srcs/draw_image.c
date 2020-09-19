/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:08:49 by Bastian           #+#    #+#             */
/*   Updated: 2020/08/19 11:24:35 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_ceilling(t_mlx **mlx, int rgb[3], unsigned int color)
{
	color = (*mlx)->cub.c;
	rgb[0] = (color & 0xff0000) >> 16;
	rgb[1] = (color & 0xff00) >> 8;
	rgb[2] = (color & 0xff);
	if (rgb[0] > ((*mlx)->count.l / 1.35) + abs((int)(((*mlx)->cub.r[0] / 2)
					- (*mlx)->count.i)) / 9)
		rgb[0] -= (((*mlx)->count.l / 1.35) +
				abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
	else
		rgb[0] = 0;
	if (rgb[1] > ((*mlx)->count.l / 1.35) + abs((int)(((*mlx)->cub.r[0] / 2)
					- (*mlx)->count.i)) / 9)
		rgb[1] -= (((*mlx)->count.l / 1.35) +
				abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
	else
		rgb[1] = 0;
	if (rgb[2] > ((*mlx)->count.l / 1.35) + abs((int)(((*mlx)->cub.r[0] / 2)
					- (*mlx)->count.i)) / 9)
		rgb[2] -= (((*mlx)->count.l / 1.35) +
				abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
	else
		rgb[2] = 0;
	((*mlx)->image.data_rendering[(((*mlx)->count.l) *
		(*mlx)->cub.r[0]) + (int)(*mlx)->count.i]) =
		(rgb[0] << 16) + (rgb[1] << 8) + (rgb[2]);
}

void	ft_draw_floor(t_mlx **mlx, unsigned int color, int rgb[3])
{
	color = (*mlx)->cub.f;
	rgb[0] = (color & 0xff0000) >> 16;
	rgb[1] = (color & 0xff00) >> 8;
	rgb[2] = (color & 0xff);
	if ((rgb[0] > (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 +
					abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9)))
		rgb[0] -= (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 +
				abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
	else
		rgb[0] = 0;
	if ((rgb[1] > (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 +
					abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9)))
		rgb[1] -= (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 +
				abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
	else
		rgb[1] = 0;
	if ((rgb[2] > (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 +
					abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9)))
		rgb[2] -= (((*mlx)->cub.r[1] - (*mlx)->count.l) / 1.35 +
				abs((int)(((*mlx)->cub.r[0] / 2) - (*mlx)->count.i)) / 9);
	else
		rgb[2] = 0;
	((*mlx)->image.data_rendering[((*mlx)->count.l *
		(*mlx)->cub.r[0]) + (int)(*mlx)->count.i]) =
		(rgb[0] << 16) + (rgb[1] << 8) + (rgb[2]);
}

void	ft_draw_wall(t_mlx **mlx, unsigned int color, int rgb[3])
{
	(*mlx)->image.text_y = (int)(*mlx)->image.text_pos;
	(*mlx)->image.text_pos += (*mlx)->image.step;
	color = (*mlx)->image.data_img[(*mlx)->image.height *
		(*mlx)->image.text_y + (*mlx)->image.text_x];
	rgb[0] = (color & 0xff0000) >> 16;
	rgb[1] = (color & 0xff00) >> 8;
	rgb[2] = (color & 0xff);
	if ((*mlx)->space.wall_dist > 2)
	{
		((*mlx)->image.data_rendering[((*mlx)->count.l *
			(*mlx)->cub.r[0]) + (int)(*mlx)->count.i]) =
			(((int)(rgb[0] / (((*mlx)->space.wall_dist / 2)))) << 16) +
			(((int)(rgb[1] / (((*mlx)->space.wall_dist / 2)))) << 8) +
			(((int)(rgb[2] / (((*mlx)->space.wall_dist / 2)))));
	}
	else
	{
		((*mlx)->image.data_rendering[((*mlx)->count.l *
			(*mlx)->cub.r[0]) + (int)(*mlx)->count.i]) =
			(rgb[0] << 16) +
			(rgb[1] << 8) +
			(rgb[2]);
	}
}

void	ft_draw_image(t_mlx **mlx)
{
	unsigned int	color;
	int				rgb[3];

	color = 0;
	(*mlx)->count.l = -1;
	while ((*mlx)->count.l++ < (*mlx)->draw.draw_start - 1)
		ft_draw_ceilling(mlx, rgb, color);
	(*mlx)->count.l--;
	while ((*mlx)->count.l++ < (*mlx)->draw.draw_end - 1)
		ft_draw_wall(mlx, color, rgb);
	(*mlx)->count.l--;
	while ((*mlx)->count.l++ < (*mlx)->cub.r[1] - 1)
		ft_draw_floor(mlx, color, rgb);
}
