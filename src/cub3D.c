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

#include "../includes/cub3D.h"

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
	error_code = check_textures(cube);
	if (error_code)
		return (error_code);
	if (normalize_map_lines(&cube->temp_map) != 0)
		return (8);
	error_code = validate_map(cube);
	if (error_code != 0)
		return (error_code);
	return (0);
}

int	init_struct(t_cube *cube)
{
	if (!cube->player)
	{
		cube->player = malloc(sizeof(t_player));
		if (!cube->player)
			return (1);
		ft_memset(cube->player, 0, sizeof(t_player));
	}
	if (!cube->img)
	{
		cube->img = malloc(sizeof(t_textures));
		if (!cube->img)
			return (free(cube->player), 1);
		ft_memset(cube->img, 0, sizeof(t_textures));
	}
	if (!cube->hooks)
	{
		cube->hooks = malloc(sizeof(t_hook));
		if (!cube->hooks)
			return (free(cube->player), free(cube->img), 1);
		ft_memset(cube->hooks, 0, sizeof(t_hook));
	}
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
		return (clean_data(cube), 1);
	cube->mlx = mlx_init();
	if (load_textures(cube))
		return (close_game(cube), 0);
	start_game(cube);
	return (0);
}
