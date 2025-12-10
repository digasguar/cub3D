/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:15:03 by oiahidal          #+#    #+#             */
/*   Updated: 2025/11/25 12:45:13 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

void	clean_data(t_cube *data)
{
	int	i;

	i = 0;
	free_textures(data);
	if (data->hooks)
		free(data->hooks);
	if (data->player)
		free(data->player);
	if (data->mlx && data->mlx_window)
		mlx_destroy_window(data->mlx, data->mlx_window);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	free_parse_data(data);
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

void	start_game(t_cube *cube)
{
	cube->mlx_window = mlx_new_window(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"cub3d");
	init_player(cube);
	mlx_hook(cube->mlx_window, 2, 1L << 0, keyprees, cube);
	mlx_hook(cube->mlx_window, 3, 1L << 1, keyrelease, cube);
	mlx_hook(cube->mlx_window, 17, 0, close_game, cube);
	mlx_loop_hook(cube->mlx, game_loop, cube);
	mlx_loop(cube->mlx);
}

int	close_game(t_cube *data)
{
	clean_data(data);
	exit(0);
	return (0);
}
