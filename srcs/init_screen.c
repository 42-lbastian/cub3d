/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bastian <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:39:26 by Bastian           #+#    #+#             */
/*   Updated: 2020/06/25 11:14:38 by Bastian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


static int ft_give_xy_map(t_cub *cub, int fact)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < ft_size_map(cub->size_map))
	{
		while (j < cub->size_map[i])
		{
			if (cub->map[i][j] > 20)
			{
				if (fact == 1)
					return (i);
				else
					return (j);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

static int ft_position_player(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < ft_size_map(cub->size_map))
	{
		while (j < cub->size_map[i])
		{
			if (cub->map[i][j] == 30) //North
				return (1);
			if (cub->map[i][j] == 39) //West
				return (0);
			if (cub->map[i][j] == 35) //South
				return (3);
			if (cub->map[i][j] == 21) //East
				return (2);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int		ft_draw_screen(t_mlx **mlx)
{
	double i;

	for (i = 0; i < (*mlx)->cub.r[0]; i++) //cub.r[0] = largeur de l'ecran - permet de traiter toutes les lignes verticales
	{
		(*mlx)->space.hit = 0;
		(*mlx)->vect.camera_x = 2 * i / (double)(*mlx)->cub.r[0] - 1; //camera_x = coordonnee x (-1 gauche - 1 droite - 0 milieu)
		(*mlx)->vect.raydir_x = (*mlx)->vect.dir_x + (*mlx)->vect.plane_x * (*mlx)->vect.camera_x; //direction vecteur x (somme direction_vector & une partie du plane vector)
		(*mlx)->vect.raydir_y = (*mlx)->vect.dir_y + (*mlx)->vect.plane_y * (*mlx)->vect.camera_x;
		//Ray direction sum direction vector and a part of plane vector - for both coordination x and y
		(*mlx)->space.map_x = (*mlx)->space.pos_x; // position x de case dans laquelle on est
		(*mlx)->space.map_y = (*mlx)->space.pos_y; // position y de case dans laquelle on est
		(*mlx)->vect.delta_dist_x = fabs(1 / (*mlx)->vect.raydir_x); //dela_dist_x = distance que le rayon doit traverser pour aller du cote d'un carre a l'autre(cote x)
		(*mlx)->vect.delta_dist_y = fabs(1 / (*mlx)->vect.raydir_y); //dela_dist_y = distance que le rayon doit traverser pour aller du cote d'un carre a l'autre(cote y)
		if ((*mlx)->vect.raydir_x < 0)
		{
			(*mlx)->space.step_x = -1; //direction x vers laquelle se deplacer (-1 = North - Haut) sur la carte
			(*mlx)->vect.side_dist_x = ((*mlx)->space.pos_x - (*mlx)->space.map_x) * (*mlx)->vect.delta_dist_x; //side_dist_x = distance joueur - mur le plus proche de North
		}
		else
		{
			(*mlx)->space.step_x = 1; //direction x vers laquelle se deplacer (+1 = Sud - Bas) sur la carte
			(*mlx)->vect.side_dist_x = ((*mlx)->space.map_x + 1.0 - (*mlx)->space.pos_x) * (*mlx)->vect.delta_dist_x; //side_dist_x = distance joueur - mur le plus proche de South
		}
		if ((*mlx)->vect.raydir_y < 0)
		{
			(*mlx)->space.step_y = -1; //direction x vers laquelle se deplacer (-1 = West - Gauche) sur la carte
			(*mlx)->vect.side_dist_y = ((*mlx)->space.pos_y - (*mlx)->space.map_y) * (*mlx)->vect.delta_dist_y; //side_dist_y = distance joueur - mur le plus proche de West
		}
		else
		{
			(*mlx)->space.step_y = 1; //direction x vers laquelle se deplacer (+1 = East - Droite) sur la carte
			(*mlx)->vect.side_dist_y = ((*mlx)->space.map_y + 1.0 - (*mlx)->space.pos_y) * (*mlx)->vect.delta_dist_y; //side_dist-y = distance joueur - mur le plus proche de East
		}
		double texPos;
		int texX;
		double step;
		while ((*mlx)->space.hit == 0) //Tant que l'on a pas rencontre un 1 (mur)
		{
			if ((*mlx)->vect.side_dist_x < (*mlx)->vect.side_dist_y) // si oriente selon angle x (NORTH ou SOUTH)
			{
				(*mlx)->vect.side_dist_x += (*mlx)->vect.delta_dist_x; //distance mur x joueur
				(*mlx)->space.map_x += (*mlx)->space.step_x; //incrementation index map
				(*mlx)->space.side = 0; //Quel cote du mur on a tape (x - haut/bas ou 1 - gauche/droite)
			}
			else
			{
				(*mlx)->vect.side_dist_y += (*mlx)->vect.delta_dist_y; //distance mur y joueur
				(*mlx)->space.map_y += (*mlx)->space.step_y; //incrementation index map
				(*mlx)->space.side = 1; //Quel cote du mur on a tape (x - haut/bas ou y - gauche/droite)
			}
			if ((*mlx)->cub.map[(*mlx)->space.map_x][(*mlx)->space.map_y] == 1) //Si mur rencontre
			{
				(*mlx)->space.hit = 1;
				if ((*mlx)->space.side == 0 && (*mlx)->vect.raydir_x != 0)
					(*mlx)->space.wall_dist = ((*mlx)->space.map_x - (*mlx)->space.pos_x + (1 - (*mlx)->space.step_x) / 2) / (*mlx)->vect.raydir_x; //calcul effet distance mur
				else if ((*mlx)->space.side != 0 && (*mlx)->vect.raydir_y != 0)
					(*mlx)->space.wall_dist = ((*mlx)->space.map_y - (*mlx)->space.pos_y + (1 - (*mlx)->space.step_y) / 2) / (*mlx)->vect.raydir_y; //calcul effet distance mur
				if ((*mlx)->space.wall_dist != 0)
					(*mlx)->draw.line_height = (*mlx)->cub.r[1] / (*mlx)->space.wall_dist;
				else
					(*mlx)->draw.line_height = (*mlx)->cub.r[1];
				(*mlx)->draw.draw_start = (-(*mlx)->draw.line_height / 2) + ((*mlx)->cub.r[1] / 2);
				if ((*mlx)->draw.draw_start < 0)
					(*mlx)->draw.draw_start = 0;
				(*mlx)->draw.draw_end = (*mlx)->draw.line_height / 2 + (*mlx)->cub.r[1] / 2;
				if ((*mlx)->draw.draw_end >= (*mlx)->cub.r[1])
					(*mlx)->draw.draw_end = (*mlx)->cub.r[1] - 1;
			//	int texNum = (*mlx)->cub.map[(*mlx)->space.map_x][(*mlx)->space.map_y] - 1;
				double wallX; //where exactly the wall was hit
				if ((*mlx)->space.side == 0)
					wallX = (*mlx)->space.pos_y + (*mlx)->space.wall_dist * (*mlx)->vect.raydir_y;
				else
					wallX = (*mlx)->space.pos_x + (*mlx)->space.wall_dist * (*mlx)->vect.raydir_x;
				wallX -= floor((wallX));
				texX = (int)((wallX * ((double)500)));
				if((*mlx)->space.side == 0 && (*mlx)->vect.raydir_x > 0)
					texX = 500 - texX - 1;
				if((*mlx)->space.side == 1 && (*mlx)->vect.raydir_y < 0)
					texX = 500 - texX - 1;
				step = 1.0 * 500 / (*mlx)->draw.line_height;
					// Starting texture coordinate
				texPos = ((*mlx)->draw.draw_start - (*mlx)->cub.r[1]  / 2 + (*mlx)->draw.line_height / 2) * step;
		/*		if (ft_comp_float((*mlx)->space.side, 0))
				{
					if (((((*mlx)->space.old_wall_dist - (*mlx)->space.wall_dist) > 0.000001 && (*mlx)->vect.dir_y < 0) || (((*mlx)->space.wall_dist - (*mlx)->space.old_wall_dist) > 0.000001 && (*mlx)->vect.dir_y > 0)) || (*mlx)->vect.dir_x < -0.5)
						(*mlx)->draw.color = mlx_get_color_value((*mlx)->mlx_init, (0 << 16) + (0 << 8) + 0);
					else
						(*mlx)->draw.color = mlx_get_color_value((*mlx)->mlx_init, (255 << 16) + (0 << 8) + 0);
				}
				else if (ft_comp_float((*mlx)->space.side, 1))
				{
					if (((((*mlx)->space.old_wall_dist - (*mlx)->space.wall_dist) > 0.000001 && (*mlx)->vect.dir_x < 0) || (((*mlx)->space.wall_dist - (*mlx)->space.old_wall_dist) > 0.000001 && (*mlx)->vect.dir_x > 0)) || (*mlx)->vect.dir_y < -0.5)
						(*mlx)->draw.color = mlx_get_color_value((*mlx)->mlx_init, (0 << 16) + (0 << 8) + 255);
					else
						(*mlx)->draw.color = mlx_get_color_value((*mlx)->mlx_init, (0 << 16) + (255 << 8) + 0);
				}
				*/
				(*mlx)->space.old_wall_dist = (*mlx)->space.wall_dist;
			}
		}

		for (int l = 0; l < (*mlx)->draw.draw_start; l++)
			mlx_pixel_put((*mlx)->mlx_init, (*mlx)->mlx_screen, i, l, mlx_get_color_value((*mlx)->mlx_init, (*mlx)->cub.c));
		for (int l = (*mlx)->draw.draw_start; l < (*mlx)->draw.draw_end; l++)
		{
			int texY = (int)texPos & (500 - 1);
			texPos += step;
			mlx_pixel_put((*mlx)->mlx_init, (*mlx)->mlx_screen, i, l, (*mlx)->image.data[500 * texY + texX]);
		}
		for (int l = (*mlx)->draw.draw_end; l < (*mlx)->cub.r[1]; l++)
			mlx_pixel_put((*mlx)->mlx_init, (*mlx)->mlx_screen, i, l,  mlx_get_color_value((*mlx)->mlx_init, (*mlx)->cub.f));
	}
	return (1);
}

int             close_mlx(int keycode, t_mlx **mlx)
{
	double old_dir_x;
	double old_plane_x;

	if (keycode == 65307) //ESC
	{
		mlx_destroy_window((*mlx)->mlx_init, (*mlx)->mlx_screen);
		exit(0);
	}
	if (keycode == 119) //W
	{
		if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x + (*mlx)->vect.dir_x * (*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] != 1)
			(*mlx)->space.pos_x += (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
		if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x )][((int)((*mlx)->space.pos_y + (*mlx)->vect.dir_y * (*mlx)->move.move_speed))] != 1)
			(*mlx)->space.pos_y += (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
	}
	if (keycode == 115) //S
	{
		if ((*mlx)->cub.map[((int)((*mlx)->space.pos_x - (*mlx)->vect.dir_x * (*mlx)->move.move_speed))][((int)((*mlx)->space.pos_y))] != 1)
			(*mlx)->space.pos_x -= (*mlx)->vect.dir_x * (*mlx)->move.move_speed;
		if ((*mlx)->cub.map[((int)(*mlx)->space.pos_x )][((int)((*mlx)->space.pos_y - (*mlx)->vect.dir_y * (*mlx)->move.move_speed))] != 1)
			(*mlx)->space.pos_y -= (*mlx)->vect.dir_y * (*mlx)->move.move_speed;
	}
	if (keycode == 100) //D
	{
		old_dir_x = (*mlx)->vect.dir_x;
		old_plane_x = (*mlx)->vect.plane_x;
		(*mlx)->vect.dir_x = (*mlx)->vect.dir_x * cos(-(*mlx)->move.rot_speed) - (*mlx)->vect.dir_y * sin(-(*mlx)->move.rot_speed);
		(*mlx)->vect.dir_y = old_dir_x * sin(-(*mlx)->move.rot_speed) + (*mlx)->vect.dir_y * cos(-(*mlx)->move.rot_speed);
		(*mlx)->vect.plane_x = (*mlx)->vect.plane_x * cos(-(*mlx)->move.rot_speed) - (*mlx)->vect.plane_y * sin(-(*mlx)->move.rot_speed);
		(*mlx)->vect.plane_y = old_plane_x * sin(-(*mlx)->move.rot_speed) + (*mlx)->vect.plane_y * cos(-(*mlx)->move.rot_speed);
	}
	if (keycode == 97) //A
	{
		old_dir_x = (*mlx)->vect.dir_x;
		old_plane_x = (*mlx)->vect.plane_x;
		(*mlx)->vect.dir_x = (*mlx)->vect.dir_x * cos((*mlx)->move.rot_speed) - (*mlx)->vect.dir_y * sin((*mlx)->move.rot_speed);
		(*mlx)->vect.dir_y = old_dir_x * sin((*mlx)->move.rot_speed) + (*mlx)->vect.dir_y * cos((*mlx)->move.rot_speed);
		(*mlx)->vect.plane_x = (*mlx)->vect.plane_x * cos((*mlx)->move.rot_speed) - (*mlx)->vect.plane_y * sin((*mlx)->move.rot_speed);
		(*mlx)->vect.plane_y = old_plane_x * sin((*mlx)->move.rot_speed) + (*mlx)->vect.plane_y * cos((*mlx)->move.rot_speed);
	}
	return (1);
}

int ft_init_screen(t_mlx *mlx)
{
	mlx->space.pos_x = ft_give_xy_map(&(mlx->cub), 1) + 0.5; //Posx joueur
	mlx->space.pos_y = ft_give_xy_map(&(mlx->cub), 0) + 0.5; //Posy joueur
	mlx->move.move_speed = 1; //1 case
	mlx->move.rot_speed =  M_PI / 45; //4 degres en radiant
	mlx->vect.dir_x = -1; //Direction vue x - (> 0 = South) (< 0 = North) sinon 0
	mlx->vect.dir_y = 0; //Direction vue y - (> 0 = East) (< 0 = West) sinon 0
	mlx->vect.plane_x = 0;
	mlx->vect.plane_y = 0.90;
	mlx->space.old_wall_dist = -1;
	if (ft_position_player(&(mlx->cub)) == 2) //EAST - Rotation Droite
	{
		mlx->vect.dir_x = 0;
		mlx->vect.dir_y = 1;
		mlx->vect.plane_x = 0.66;
		mlx->vect.plane_y = 0;
	}
	else if (ft_position_player(&(mlx->cub)) == 0) //WEST - Rotation Gauche
	{
		mlx->vect.dir_x = 0;
		mlx->vect.dir_y = -1;
		mlx->vect.plane_x = -0.66;
		mlx->vect.plane_y = 0;
	}
	else if (ft_position_player(&(mlx->cub)) == 3) //SOUTH - Double rotation
	{
		mlx->vect.dir_x = 1;
		mlx->vect.dir_y = 0;
		mlx->vect.plane_x = 0;
		mlx->vect.plane_y = -0.66;
	}
	int bpp, sizeline,endian;
	(mlx)->image.data = (unsigned int *)mlx_get_data_addr(mlx->image.south, &bpp, &sizeline, &endian);
	mlx->mlx_screen = mlx_new_window(mlx->mlx_init, mlx->cub.r[0], mlx->cub.r[1], "Cub3D");
	mlx_hook(mlx->mlx_screen, 2, 1L<<0, close_mlx, &mlx);
	mlx_loop_hook(mlx->mlx_init, ft_draw_screen, &mlx);
	mlx_loop(mlx->mlx_init);
	return (0);
}
