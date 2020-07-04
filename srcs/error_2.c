/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 11:22:49 by Bastian           #+#    #+#             */
/*   Updated: 2020/06/26 11:55:28 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			ft_verif_joueur(t_cub cub)
{
	int i;
	int j;
	int compt;

	compt = 0;
	i = 0;
	j = 0;
	while (i < ft_size_map(cub.size_map))
	{
		while (j < cub.size_map[i])
		{
			if (cub.map[i][j] == 30 || cub.map[i][j] == 35 ||
			cub.map[i][j] == 21 || cub.map[i][j] == 39)
				compt++;
			j++;
		}
		j = 0;
		i++;
	}
	if (compt == 1)
		return (0);
	return (1);
}

static int	ft_verif_map_2(t_cub cub, int j, int i, int z)
{
	while (i < ft_size_map(cub.size_map) - 1)
	{
		j = 0;
		if ((cub.map[i][0] != 1 && cub.map[i][0] != 3) ||
		(cub.map[i][(cub.size_map[i] - 1)] != 1 &&
		cub.map[i][(cub.size_map[i] - 1)] != 3))
			return (1);
		while (j < cub.size_map[i])
		{
			z = 1;
			if ((cub.size_map[i - 1] <= (j + 1) && cub.map[i][j] != 1)
			&& cub.map[i][j] != 3)
				return (1);
			if ((cub.size_map[i + 1] <= (j + 1) && cub.map[i][j] != 1)
			&& cub.map[i][j] != 3)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int			ft_verif_map(t_cub cub)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (j < cub.size_map[0])
	{
		if (cub.map[0][j] != 1 && cub.map[0][j] != 3)
			return (1);
		j++;
	}
	if (ft_verif_map_2(cub, j, i, 0))
		return (1);
	j = 0;
	while (j < cub.size_map[ft_size_map(cub.size_map)])
	{
		if (cub.map[ft_size_map(cub.size_map)][j] != 1)
			return (1);
		j++;
	}
	return (0);
}

int			ft_verif_sprites(t_mlx *mlx)
{
	if (!((mlx->image.south = mlx_xpm_file_to_image(mlx->mlx_init, mlx->cub.path_s, &mlx->image.width, &mlx->image.height)) && mlx->image.south))
		return (1);
	if (!((mlx->image.north = mlx_xpm_file_to_image(mlx->mlx_init, mlx->cub.path_n, &mlx->image.width, &mlx->image.height)) && mlx->image.north))
		return (1);
	if (!((mlx->image.east = mlx_xpm_file_to_image(mlx->mlx_init, mlx->cub.path_e, &mlx->image.width, &mlx->image.height)) && mlx->image.east))
		return (1);
	if (!((mlx->image.west = mlx_xpm_file_to_image(mlx->mlx_init, mlx->cub.path_w, &mlx->image.width, &mlx->image.height)) && mlx->image.west))
		return (1);
	if (!((mlx->image.sprite = mlx_xpm_file_to_image(mlx->mlx_init, mlx->cub.path_sp, &mlx->image.width, &mlx->image.height)) && mlx->image.sprite))
		return (1);
	return (0);
}
