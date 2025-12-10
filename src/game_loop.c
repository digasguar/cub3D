/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:39:02 by dgasco-g          #+#    #+#             */
/*   Updated: 2025/11/21 21:33:03 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	game_loop(t_cube *cube)
{
	move_player(cube);
	render(cube);
	return (1);
}

int	keyprees(int keycode, t_cube *cube)
{
	if (keycode == 119)
		cube->hooks->w = 1;
	if (keycode == 115)
		cube->hooks->s = 1;
	if (keycode == 97)
		cube->hooks->a = 1;
	if (keycode == 100)
		cube->hooks->d = 1;
	if (keycode == 65361)
		cube->hooks->left = 1;
	if (keycode == 65363)
		cube->hooks->right = 1;
	if (keycode == 65307)
		close_game(cube);
	return (0);
}

int	keyrelease(int keycode, t_cube *cube)
{
	if (keycode == 119)
		cube->hooks->w = 0;
	if (keycode == 115)
		cube->hooks->s = 0;
	if (keycode == 97)
		cube->hooks->a = 0;
	if (keycode == 100)
		cube->hooks->d = 0;
	if (keycode == 65361)
		cube->hooks->left = 0;
	if (keycode == 65363)
		cube->hooks->right = 0;
	return (0);
}
