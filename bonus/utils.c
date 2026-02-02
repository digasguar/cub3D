/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:31:33 by dgasco-g          #+#    #+#             */
/*   Updated: 2025/11/25 12:45:29 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	mouse_move(int x, int y, t_cube *cube)
{
	int	delta_x;
	int	center_x;
	int	center_y;

	if (!cube->hiden_mouse)
	{
		cube->hiden_mouse = 1;
		mlx_mouse_hide(cube->mlx, cube->mlx_window);
	}
	center_x = SCREEN_WIDTH / 2;
	center_y = SCREEN_HEIGHT / 2;
	(void)y;
	delta_x = x - center_x;
	if (delta_x > 5)
		move_camera(65363, cube);
	else if (delta_x < -5)
		move_camera(65361, cube);
	mlx_mouse_move(cube->mlx, cube->mlx_window, center_x, center_y);
	return (0);
}

void	free_textures(t_cube *data)
{
	if (data->textures[0].img)
		mlx_destroy_image(data->mlx, data->textures[0].img);
	if (data->textures[1].img)
		mlx_destroy_image(data->mlx, data->textures[1].img);
	if (data->textures[2].img)
		mlx_destroy_image(data->mlx, data->textures[2].img);
	if (data->textures[3].img)
		mlx_destroy_image(data->mlx, data->textures[3].img);
	if (data->img->img)
		mlx_destroy_image(data->mlx, data->img->img);
	if (data->img)
		free(data->img);
}

int	init_substructs(t_cube *cube)
{
	cube->player = malloc(sizeof(t_player));
	cube->img = malloc(sizeof(t_textures));
	cube->hooks = malloc(sizeof(t_hook));
	if (!cube->player || !cube->img || !cube->hooks)
		return (1);
	ft_memset(cube->player, 0, sizeof(t_player));
	ft_memset(cube->img, 0, sizeof(t_textures));
	ft_memset(cube->hooks, 0, sizeof(t_hook));
	return (0);
}
