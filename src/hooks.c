/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 05:35:41 by dgasco-g          #+#    #+#             */
/*   Updated: 2025/11/25 16:03:10 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_camera(int keycode, t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotation;

	if (keycode == 65361)
		rotation = -CAMERA_SPEED;
	else if (keycode == 65363)
		rotation = CAMERA_SPEED;
	else
		return ;
	old_dir_x = cube->player->camerax;
	cube->player->camerax = cube->player->camerax * cos(rotation)
		- cube->player->cameray * sin(rotation);
	cube->player->cameray = old_dir_x * sin(rotation) + cube->player->cameray
		* cos(rotation);
	old_plane_x = cube->player->plane_x;
	cube->player->plane_x = cube->player->plane_x * cos(rotation)
		- cube->player->plane_y * sin(rotation);
	cube->player->plane_y = old_plane_x * sin(rotation) + cube->player->plane_y
		* cos(rotation);
}

void	move_up(t_cube *cube)
{
	double	new_x;
	double	new_y;
	int		mx;
	int		my;

	new_x = cube->player->player_x + cube->player->camerax * PLAYER_SPEED;
	new_y = cube->player->player_y + cube->player->cameray * PLAYER_SPEED;
	mx = (int)(new_x + cube->player->camerax * COLLISION);
	my = (int)(new_y + cube->player->cameray * COLLISION);
	if (mx >= 0 && mx < cube->maxx && my >= 0 && my < cube->maxy
		&& cube->map[my][mx] != '1')
	{
		if (cube->map[(int)cube->player->player_y][mx] != '1')
			cube->player->player_x = new_x;
		if (cube->map[my][(int)cube->player->player_x] != '1')
			cube->player->player_y = new_y;
	}
}

void	move_down(t_cube *cube)
{
	double	new_x;
	double	new_y;
	int		mx;
	int		my;

	new_x = cube->player->player_x - cube->player->camerax * PLAYER_SPEED;
	new_y = cube->player->player_y - cube->player->cameray * PLAYER_SPEED;
	mx = (int)(new_x - cube->player->camerax * COLLISION);
	my = (int)(new_y - cube->player->cameray * COLLISION);
	if (mx >= 0 && mx < cube->maxx && my >= 0 && my < cube->maxy
		&& cube->map[my][mx] != '1')
	{
		if (cube->map[(int)cube->player->player_y][mx] != '1')
			cube->player->player_x = new_x;
		if (cube->map[my][(int)cube->player->player_x] != '1')
			cube->player->player_y = new_y;
	}
}

void	move_left(t_cube *cube)
{
	double	new_x;
	double	new_y;
	int		mx;
	int		my;

	new_x = cube->player->player_x - cube->player->plane_x * PLAYER_SPEED;
	new_y = cube->player->player_y - cube->player->plane_y * PLAYER_SPEED;
	mx = (int)(new_x - cube->player->plane_x * COLLISION);
	my = (int)(new_y - cube->player->plane_y * COLLISION);
	if (mx >= 0 && mx < cube->maxx && my >= 0 && my < cube->maxy
		&& cube->map[my][mx] != '1')
	{
		if (cube->map[(int)cube->player->player_y][mx] != '1')
			cube->player->player_x = new_x;
		if (cube->map[my][(int)cube->player->player_x] != '1')
			cube->player->player_y = new_y;
	}
}

void	move_right(t_cube *cube)
{
	double	new_x;
	double	new_y;
	int		mx;
	int		my;

	new_x = cube->player->player_x + cube->player->plane_x * PLAYER_SPEED;
	new_y = cube->player->player_y + cube->player->plane_y * PLAYER_SPEED;
	mx = (int)(new_x + cube->player->plane_x * COLLISION);
	my = (int)(new_y + cube->player->plane_y * COLLISION);
	if (mx >= 0 && mx < cube->maxx && my >= 0 && my < cube->maxy
		&& cube->map[my][mx] != '1')
	{
		if (cube->map[(int)cube->player->player_y][mx] != '1')
			cube->player->player_x = new_x;
		if (cube->map[my][(int)cube->player->player_x] != '1')
			cube->player->player_y = new_y;
	}
}
