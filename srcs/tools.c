/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:45:23 by Bastian           #+#    #+#             */
/*   Updated: 2020/06/23 11:02:31 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int		ft_size_map(int *size_map)
{
	int i;

	i = 0;
	if (size_map)
	{
		while (size_map[i] != -1)
			i++;
		return (i);
	}
	else
		return (0);
}

int		ft_comp_float(float nb_1, float nb_2)
{
	if (abs((((int)(nb_1 * 10000))) - (((int)(nb_2 * 10000)))))
		return (0);
	else
		return (1);
}
