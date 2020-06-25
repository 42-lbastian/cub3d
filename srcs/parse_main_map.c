/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:37:29 by Bastian           #+#    #+#             */
/*   Updated: 2020/06/18 10:45:16 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	parse_map_init(int fd2, int fd3)
{
	char c;
	c = 0;

	while (1)
	{
		if (c != '\n' && read(fd3, &c, 1) > 0 && read(fd2, &c, 1) > 0)
		{
		}
		if (c == '\n')
		{
			read(fd2, &c, 1);
			if (c == ' ' || c == '1' || c == '2' || c == '0')
				break ;
			else
				read(fd3, &c, 1);
		}
	}
}

static int	parse_map_fill(int fd2, int fd3, t_cub *cub, int count)
{
	char	c;
	int		i;
	int		y;

	i = -1;
	while (++i < count)
	{
		while (read(fd2, &c, 1) > 0 && c != '\n')
			cub->size_map[i]++;
		if (!(cub->map[i] = malloc(sizeof(int) * cub->size_map[i])))
			cub->map = NULL;
		y = 0;
		while (read(fd3, &c, 1) > 0 && c != '\n')
		{
			if (c == ' ')
				cub->map[i][y] = 3;
			else if (c == '1' || c == '2' || c == '0' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W')
				cub->map[i][y] = c - '0';
			else
				return (1);
			y++;
		}
	}
	return (0);
}

static int	parse_map(int fd, char *str, t_cub *cub)
{
	int count;
	int fd2;
	int fd3;

	count = count_lines_map(fd);
	if (!((cub->map = malloc(sizeof(int*) * count))))
		cub->map = NULL;
	if (!(cub->size_map = malloc(sizeof(int) * (count + 1))))
		cub->map = NULL;
	init_size_cub(cub, count);
	if ((fd2 = open(str, O_RDONLY)) != -1)
	{
		if ((fd3 = open(str, O_RDONLY)) != -1)
		{
			parse_map_init(fd2, fd3);
			if (parse_map_fill(fd2, fd3, cub, count))
				return (1);
			close(fd3);
		}
		close(fd2);
	}
	return (0);
}

int			ft_parse_2(char c, t_cub *cub, int fd, int error)
{
	if (c == 'R')
		error += ft_parse_r(fd, cub->r);
	else if (c == 'F')
		error += ft_parse_fc(fd, &cub->f, 0, "floor");
	else if (c == 'C')
		error += ft_parse_fc(fd, &cub->c, 0, "ceilling");
	else if (c == 'S')
		error += ft_parse_news(fd, cub->path_sp, ' ', cub);
	else if (c == 'N')
		error += ft_parse_news(fd, cub->path_n, 'O', cub);
	else if (c == 'W')
		error += ft_parse_news(fd, cub->path_w, 'E', cub);
	else if (c == 'E')
		error += ft_parse_news(fd, cub->path_e, 'A', cub);
	else if (c != ' ' && c != '\n' && c != '1')
		return (1);
	return (error);
}

int			ft_parse(char *str, t_cub *cub, int fd)
{
	char c;

	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			read(fd, &c, 1);
			if (c == ' ' || c == '1' || c == '2' || c == '0')
				if (parse_map(fd, str, cub))
					return (1);
		}
		if (ft_parse_2(c, cub, fd, 0))
			return (1);
	}
	return (0);
}
