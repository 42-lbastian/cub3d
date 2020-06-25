/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 10:49:32 by Bastian           #+#    #+#             */
/*   Updated: 2020/06/18 10:54:01 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_cub(t_cub *cub)
{
	cub->r[0] = 0;
	cub->r[1] = 0;
	cub->f = 0;
	cub->c = 0;
	cub->path_s[0] = '\0';
	cub->path_sp[0] = '\0';
	cub->path_n[0] = '\0';
	cub->path_w[0] = '\0';
	cub->path_e[0] = '\0';
	cub->size_map = NULL;
}

static void	free_cub(t_cub *cub)
{
	int i;

	i = 0;
	if (ft_size_map(cub->size_map) > 0)
	{
		while (i < ft_size_map(cub->size_map))
		{
			if (cub->map[i])
				free(cub->map[i]);
			else
				break;
			i++;
		}
		free(cub->map);
		free(cub->size_map);
	}
}

int			main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		fd;

	if (argc == 2)
	{
		if (!(mlx = malloc(sizeof(t_mlx))))
			return (0);
		init_cub(&(mlx->cub));
		if ((ft_strcmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub")) ||
		((fd = open(argv[1], O_RDONLY)) == -1) || ft_parse(argv[1], &(mlx->cub), fd))
		{
			ft_putstr("Erreur\nfichier non valide\n");
			free_cub(&(mlx->cub));
			free(mlx);
			return (0);
		}
		close(fd);
		mlx->mlx_init = mlx_init();
		if (ft_check_data((mlx)))
			ft_init_screen((mlx));
		free_cub(&(mlx->cub));
		free((mlx));
	}
	else
		ft_putstr("Erreur\nTrop D'arguments\n");
	return (0);
}
