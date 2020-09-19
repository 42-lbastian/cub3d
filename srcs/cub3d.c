/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 10:49:32 by Bastian           #+#    #+#             */
/*   Updated: 2020/09/15 19:12:52 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_cub(t_cub *cub)
{
	cub->nb_sprites = 0;
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

void		free_cub(t_cub *cub)
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
				break ;
			i++;
		}
		free(cub->map);
		free(cub->size_map);
	}
}

int			ft_free_all(t_mlx **mlx)
{
	(*mlx)->count.i = -1;
	mlx_destroy_image((*mlx)->mlx_init, (*mlx)->image.img_rendering);
	while ((*mlx)->count.i++ < (*mlx)->cub.nb_sprites - 1)
		free((*mlx)->sprite.specs[(int)(*mlx)->count.i]);
	free((*mlx)->sprite.specs);
	mlx_destroy_image((*mlx)->mlx_init, (*mlx)->image.north);
	mlx_destroy_image((*mlx)->mlx_init, (*mlx)->image.south);
	mlx_destroy_image((*mlx)->mlx_init, (*mlx)->image.east);
	mlx_destroy_image((*mlx)->mlx_init, (*mlx)->image.west);
	mlx_destroy_image((*mlx)->mlx_init, (*mlx)->sprite.sprite);
	free_cub(&((*mlx)->cub));
	free((*mlx)->mlx_init);
	free(*mlx);
	exit(0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		fd;

	if (argc == 2 || argc == 3)
	{
		if (argc == 3 && ft_strcmp(argv[2], "--save"))
			return (ft_invalid_arg());
		if (!(mlx = malloc(sizeof(t_mlx))))
			return (0);
		mlx->cub.save = 0;
		if (argc == 3)
			mlx->cub.save = 1;
		init_cub(&(mlx->cub));
		if ((ft_strcmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub")) || ((fd =
		open(argv[1], O_RDONLY)) == -1) || ft_parse(argv[1], &(mlx->cub), fd))
			return (ft_invalid_file(&mlx));
		close(fd);
		mlx->mlx_init = mlx_init();
		ft_fuck_norm_27_to_25(mlx);
		free_cub(&(mlx->cub));
		free((mlx));
	}
	else
		ft_putstr("Erreur\nTrop D'arguments\n");
	return (0);
}
