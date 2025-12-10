/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:17:26 by dgasco-g          #+#    #+#             */
/*   Updated: 2025/11/25 16:03:10 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	player_direction_aux(t_player *player, char c)
{
	if (c == 'E')
	{
		player->camerax = 1;
		player->cameray = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	if (c == 'W')
	{
		player->camerax = -1;
		player->cameray = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void	player_direction(t_player *player, char c)
{
	if (c == 'N')
	{
		player->camerax = 0;
		player->cameray = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	if (c == 'S')
	{
		player->camerax = 0;
		player->cameray = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else
		player_direction_aux(player, c);
}

void	init_player(t_cube *cube)
{
	int		y;
	int		x;
	char	p;

	y = -1;
	while (++y < cube->maxy)
	{
		x = -1;
		while (++x < cube->maxx)
		{
			p = cube->map[y][x];
			if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
			{
				cube->player->player_x = x + 0.5;
				cube->player->player_y = y + 0.5;
				cube->map[y][x] = '0';
				player_direction(cube->player, p);
				return ;
			}
		}
	}
}

void	move_player(t_cube *cube)
{
	if (cube->hooks->w)
		move_up(cube);
	if (cube->hooks->s)
		move_down(cube);
	if (cube->hooks->d)
		move_right(cube);
	if (cube->hooks->a)
		move_left(cube);
	if (cube->hooks->left)
		move_camera(65361, cube);
	if (cube->hooks->right)
		move_camera(65363, cube);
}
