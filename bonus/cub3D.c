/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:06:58 by oiahidal          #+#    #+#             */
/*   Updated: 2025/11/25 16:02:28 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

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

int	close_game(t_cube *data)
{
	clean_data(data);
	exit(0);
	return (0);
}

void	init_data(t_cube *cube, char *map_file)
{
	ft_memset(cube, 0, sizeof(t_cube));
	cube->fcolor[0] = -1;
	cube->fcolor[1] = -1;
	cube->fcolor[2] = -1;
	cube->ccolor[0] = -1;
	cube->ccolor[1] = -1;
	cube->ccolor[2] = -1;
	cube->ids = NULL;
	cube->map_fd = open(map_file, O_RDONLY);
}

static int	parse(t_cube *cube, int argc, char **argv)
{
	int	error_code;

	cube->ids = malloc(sizeof(t_ids));
	if (!cube->ids)
		exit_error(8, cube);
	ft_memset(cube->ids, 0, sizeof(t_ids));
	error_code = is_valid_args(argc, argv, cube);
	if (error_code)
		return (error_code);
	if (parse_file(cube, cube->map_fd) != 0)
		return (4);
	if (normalize_map_lines(&cube->temp_map) != 0)
		return (8);
	error_code = validate_map(cube);
	if (error_code != 0)
		return (6);
	return (0);
}

int	main(int argc, char **args)
{
	t_cube	*cube;
	int		error;

	cube = malloc(sizeof(t_cube));
	if (!cube)
		return (1);
	init_data(cube, args[1]);
	error = parse(cube, argc, args);
	if (error)
		exit_error(error, cube);
	if (init_substructs(cube))
		return (clean_data(cube), 0);
	cube->mlx = mlx_init();
	if (load_textures(cube))
		return (close_game(cube), 0);
	cube->mlx_window = mlx_new_window(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"cub3d");
	init_player(cube);
	mlx_hook(cube->mlx_window, 2, 1L << 0, keyprees, cube);
	mlx_hook(cube->mlx_window, 3, 1L << 1, keyrelease, cube);
	mlx_hook(cube->mlx_window, 17, 0, close_game, cube);
	mlx_hook(cube->mlx_window, 6, 1L << 6, mouse_move, cube);
	mlx_loop_hook(cube->mlx, game_loop, cube);
	mlx_loop(cube->mlx);
}
