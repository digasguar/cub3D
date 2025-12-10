/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiahidal <oiahidal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 23:13:14 by dgasco-g          #+#    #+#             */
/*   Updated: 2025/11/25 15:22:54 by oiahidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	load_textures_aux(t_cube *cube)
{
	cube->textures[2].img = mlx_xpm_file_to_image(cube->mlx,
			cube->wtex,
			&cube->textures[2].width, &cube->textures[2].height);
	if (!cube->textures[2].img)
		return (printf("Error\nTexture WE failed\n"), 1);
	cube->textures[2].addr = mlx_get_data_addr(cube->textures[2].img,
			&cube->textures[2].bits_per_pixel, &cube->textures[2].line_length,
			&cube->textures[2].endian);
	cube->textures[3].img = mlx_xpm_file_to_image(cube->mlx,
			cube->etex,
			&cube->textures[3].width, &cube->textures[3].height);
	if (!cube->textures[3].img)
		return (printf("Error\nTexture EA failed\n"), 1);
	cube->textures[3].addr = mlx_get_data_addr(cube->textures[3].img,
			&cube->textures[3].bits_per_pixel, &cube->textures[3].line_length,
			&cube->textures[3].endian);
	return (0);
}

int	load_textures(t_cube *cube)
{
	cube->img->img = mlx_new_image(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cube->img->img)
		return (printf("Error\nImage creation failed\n"), 1);
	cube->img->addr = mlx_get_data_addr(cube->img->img,
			&cube->img->bits_per_pixel, &cube->img->line_length,
			&cube->img->endian);
	cube->textures[0].img = mlx_xpm_file_to_image(cube->mlx,
			cube->ntex,
			&cube->textures[0].width, &cube->textures[0].height);
	if (!cube->textures[0].img)
		return (printf("Error\nTexture NO failed\n"), 1);
	cube->textures[0].addr = mlx_get_data_addr(cube->textures[0].img,
			&cube->textures[0].bits_per_pixel, &cube->textures[0].line_length,
			&cube->textures[0].endian);
	cube->textures[1].img = mlx_xpm_file_to_image(cube->mlx,
			cube->stex,
			&cube->textures[1].width, &cube->textures[1].height);
	if (!cube->textures[1].img)
		return (printf("Error\nTexture SO failed\n"), 1);
	cube->textures[1].addr = mlx_get_data_addr(cube->textures[1].img,
			&cube->textures[1].bits_per_pixel, &cube->textures[1].line_length,
			&cube->textures[1].endian);
	return (load_textures_aux(cube));
}
