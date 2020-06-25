/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_news_fc_r.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:13:21 by Bastian           #+#    #+#             */
/*   Updated: 2020/05/18 10:27:24 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_parse_news_2(int fd, char path[1024], char ale)
{
	char	c;
	int		i;

	i = 0;
	read(fd, &c, 1);
	if (c != ' ' && ale != ' ')
		return (1);
	while (c == ' ' || c == ale)
		read(fd, &c, 1);
	while (c != '\n' && c != ' ')
	{
		path[i] = c;
		i++;
		read(fd, &c, 1);
	}
	path[i] = '\0';
	while (c != '\n')
		read(fd, &c, 1);
	return (0);
}

int			ft_parse_news(int fd, char path[1024], char ale, t_cub *cub)
{
	int		i;
	char	c;

	i = 0;
	read(fd, &c, 1);
	if (c == ale)
		return (ft_parse_news_2(fd, path, ale));
	else if (c == 'O' && ale == ' ')
		return (ft_parse_news_2(fd, cub->path_s, 'O'));
	else
		return (1);
}

int			ft_parse_r(int fd, int tab[2])
{
	char	c;
	int		i;

	i = 0;
	read(fd, &c, 1);
	if (c != ' ')
		return (1);
	while (c == ' ' && c != '\n')
		read(fd, &c, 1);
	while (i < 2)
	{
		while (c != ' ' && c != '\n')
		{
			if ((c < '0' || c > '9') && c != '-')
				return (1);
			tab[i] = tab[i] * 10 + (c - '0');
			read(fd, &c, 1);
		}
		while (c == ' ' && c != '\n')
			read(fd, &c, 1);
		i++;
	}
	return (0);
}

static int	ft_check_fc(int tab[3], char *str)
{
	int error;

	error = 0;
	if (tab[0] > 255 || tab[1] > 255 || tab[2] > 255)
	{
		printf("COUCOU\t |%d||%d||%d|\n", tab[0], tab[1], tab[2]);
		ft_putstr("Erreur\nPas plus de 255 pour les couleurs de ");
		ft_putstr(str);
		ft_putstr("\n");
		error = 1;
	}
	if (tab[0] < 0 || tab[1] < 0 || tab[2] < 0)
	{
		ft_putstr("Erreur\nPas de negatif pour les couleurs de ");
		ft_putstr(str);
		ft_putstr("\n");
		error = 1;
	}
	return (error);
}

int			ft_parse_fc(int fd, int *fc, int i, char *str)
{
	char	c;
	int		tab[3];

	read(fd, &c, 1);
	if (c != ' ')
		return (1);
	while (c == ' ' && c != '\n')
		read(fd, &c, 1);
	while (i < 3)
	{
		tab[i] = 0;
		if (!((c >= '0' && c <= '9') || c == '-'))
			return (1);
		while (c != ' ' && c != ',' && c != '\n')
		{
			tab[i] = tab[i] * 10 + (c - '0');
			read(fd, &c, 1);
		}
		while ((c == ',' || c == ' ') && c != '\n' && i < 2)
			read(fd, &c, 1);
		while (c == ' ' && c != '\n' && i == 2)
			read(fd, &c, 1);
		i++;
	}
	*(fc) = (tab[0] << 16) + (tab[1] << 8) + tab[2];
	return (ft_check_fc(tab, str));
}
