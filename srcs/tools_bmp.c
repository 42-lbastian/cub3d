/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:39:14 by Bastian           #+#    #+#             */
/*   Updated: 2020/09/15 14:32:31 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr_fd(char *s, int fd, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_print_null(int nb, int fd)
{
	int i;

	i = 0;
	while (i < nb)
	{
		ft_putchar_fd('\x0', fd);
		i++;
	}
}
