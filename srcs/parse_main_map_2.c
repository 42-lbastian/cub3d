/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_map_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:26:49 by Bastian           #+#    #+#             */
/*   Updated: 2020/09/15 18:27:31 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			ft_parse_2(char c, t_cub *cub, int fd, int error)
{
	if (c == 'R')
		error += ft_parse_r(fd, cub->r);
	else if (c == 'F')
		error += ft_parse_fc(fd, &cub->f, -1, "floor");
	else if (c == 'C')
		error += ft_parse_fc(fd, &cub->c, -1, "ceilling");
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
