/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:22:32 by Bastian           #+#    #+#             */
/*   Updated: 2020/05/09 16:19:36 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		count_lines_map(int fd)
{
	int		count;
	char	c;

	count = 0;
	while (read(fd, &c, 1) > 0)
		if (c == '\n')
			count++;
	return (count);
}

void	init_size_cub(t_cub *cub, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		cub->size_map[i] = 0;
		i++;
	}
	cub->size_map[i] = -1;
	cub->size_map[0]++;
}
