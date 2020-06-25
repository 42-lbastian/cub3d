/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 10:16:01 by Bastian           #+#    #+#             */
/*   Updated: 2020/06/18 10:23:29 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	verif_line_map(t_cub cub)
{
	int i;

	i = 0;
	while (cub.size_map[i] != -1)
	{
		if (cub.size_map[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_check_data_sprites_map(t_mlx *mlx, int error)
{
	if (ft_verif_sprites(mlx))
	{
		ft_putstr("Erreur\nSprites non valides\n");
		error = 0;
	}
	if (verif_line_map(mlx->cub) || ft_verif_map(mlx->cub))
	{
		ft_putstr("Erreur\nMap non valide\n");
		error = 0;
	}
	if (ft_verif_joueur(mlx->cub))
	{
		ft_putstr("Erreur\n1 position de depart requise\n");
		error = 0;
	}
	return (error);
}

int			ft_check_data(t_mlx *mlx)
{
	int error;

	error = 1;
	if (!(mlx->cub.map))
	{
		ft_putstr("Erreur\nAllocation memoire\n");
		return (0);
	}
	if (mlx->cub.r[0] <= 0 || mlx->cub.r[1] <= 0)
	{
		ft_putstr("Erreur\nDonnee non valide pour la resolution\n");
		error = 0;
	}
	error = ft_check_data_sprites_map(mlx, error);
	return (error);
}
