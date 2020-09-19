/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:59:11 by Bastian           #+#    #+#             */
/*   Updated: 2020/09/15 14:32:04 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_give_xy_map(t_cub *cub, int fact)
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

int	ft_remove_orientation(t_cub *cub, int i, int j, int position)
{
	cub->map[i][j] = 0;
	return (position);
}

int	ft_position_player(t_cub *cub)
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
				return (ft_remove_orientation(cub, i, j, 1));
			if (cub->map[i][j] == 39)
				return (ft_remove_orientation(cub, i, j, 0));
			if (cub->map[i][j] == 35)
				return (ft_remove_orientation(cub, i, j, 3));
			if (cub->map[i][j] == 21)
				return (ft_remove_orientation(cub, i, j, 2));
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	ft_position_sprite(t_mlx **mlx)
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
				(*mlx)->sprite.specs[(*mlx)->sprite.nb][0] = i;
				(*mlx)->sprite.specs[(*mlx)->sprite.nb][1] = j;
				(*mlx)->sprite.specs[(*mlx)->sprite.nb][2] =
					(*mlx)->cub.map[i][j];
				(*mlx)->sprite.nb++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
