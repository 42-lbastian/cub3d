/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:53:22 by Bastian           #+#    #+#             */
/*   Updated: 2020/09/15 18:54:45 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_header_size(int nb, int fd)
{
	int i;
	int j;

	if (nb < 255)
	{
		ft_putchar_fd((char)nb, fd);
		ft_print_null(3, fd);
	}
	else
	{
		i = 1;
		while (256 * i < nb)
			i++;
		i--;
		j = nb - i * 256;
		ft_putchar_fd((char)j, fd);
		ft_putchar_fd((char)i, fd);
		ft_print_null(2, fd);
	}
}

int			ft_complement(int d)
{
	if ((d * 3) % 4 == 0)
		return (0);
	return (4 - ((d * 3) % 4));
}

static void	ft_bmp_write(t_mlx **mlx, int i, int k, char *str)
{
	int j;

	while (i > 0)
	{
		j = 0;
		while (j < (*mlx)->cub.r[0])
		{
			str[k] = ((*mlx)->image.data_rendering[i *
				(*mlx)->cub.r[0] + j] & 0xff);
			str[k + 1] = ((*mlx)->image.data_rendering[i *
				(*mlx)->cub.r[0] + j] & 0xffff) >> 8;
			str[k + 2] = ((*mlx)->image.data_rendering[i *
				(*mlx)->cub.r[0] + j] & 0xffffff) >> 16;
			k += 3;
			j++;
		}
		j = 0;
		while (j < ft_complement((*mlx)->cub.r[0]))
		{
			str[k] = '\x0';
			k++;
			j++;
		}
		i--;
	}
}

void		ft_magic_bmp(t_mlx **mlx)
{
	int		fd_bmp;
	int		i;
	int		k;
	char	*str;
	int		bmp_width;

	k = 0;
	bmp_width = ((*mlx)->cub.r[0] * 3) + (ft_complement(((*mlx)->cub.r[0])));
	str = malloc(sizeof(char) * (*mlx)->cub.r[1] * bmp_width);
	i = (*mlx)->cub.r[1];
	close(open("zeub.bmp", O_RDONLY | O_WRONLY | O_TRUNC));
	fd_bmp = open("zeub.bmp", O_WRONLY | O_CREAT, S_IRWXU);
	ft_putstr_fd("BM\0\0\0\0\0\0\0\0", fd_bmp, 10);
	ft_putstr_fd("\x36\0\0\0", fd_bmp, 4);
	ft_putstr_fd("\x28\0\0\0", fd_bmp, 4);
	ft_header_size((*mlx)->cub.r[0], fd_bmp);
	ft_header_size((*mlx)->cub.r[1], fd_bmp);
	ft_putstr_fd("\x01\0", fd_bmp, 2);
	ft_putstr_fd("\x18\0", fd_bmp, 2);
	ft_print_null(24, fd_bmp);
	ft_bmp_write(mlx, i, k, str);
	write(fd_bmp, str, (*mlx)->cub.r[1] * bmp_width);
	close(fd_bmp);
	free(str);
	exit(0);
}
