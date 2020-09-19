/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:11:16 by Bastian           #+#    #+#             */
/*   Updated: 2020/09/15 19:12:03 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			ft_invalid_file(t_mlx **mlx)
{
	ft_putstr("Erreur\nfichier non valide\n");
	free_cub(&((*mlx)->cub));
	free(mlx);
	return (0);
}

int			ft_invalid_arg(void)
{
	ft_putstr("Erreur\nArgument non valide");
	return (0);
}

void		ft_fuck_norm_27_to_25(t_mlx *mlx)
{
	if (ft_check_data((mlx)))
		ft_raycast_launch((mlx));
}
