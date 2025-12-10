/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:11:54 by oiahidal          #+#    #+#             */
/*   Updated: 2025/11/25 16:03:10 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E' || c == ' ');
}

static int	is_enclosed(t_cube *cube, int y, int x)
{
	if (y == 0 || y == cube->maxy - 1 || x == 0 || x == cube->maxx - 1)
		return (0);
	if (cube->map[y - 1][x] == ' ')
		return (0);
	if (cube->map[y + 1][x] == ' ')
		return (0);
	if (cube->map[y][x - 1] == ' ')
		return (0);
	if (cube->map[y][x + 1] == ' ')
		return (0);
	return (1);
}

static int	convert_list_to_array(t_cube *cube)
{
	t_tmap	*current;
	int		i;

	cube->maxy = 0;
	current = cube->temp_map;
	while (current)
	{
		cube->maxy++;
		current = current->next;
	}
	cube->map = (char **)malloc(sizeof(char *) * (cube->maxy + 1));
	if (!cube->map)
		return (1);
	current = cube->temp_map;
	i = -1;
	while (current)
	{
		cube->map[++i] = ft_strdup(current->line);
		if (!cube->map[i])
			return (1);
		current = current->next;
	}
	cube->map[++i] = NULL;
	cube->maxx = ft_strlen(cube->map[0]);
	return (cube->maxx = ft_strlen(cube->map[0]), 0);
}

static int	validate_map_row(t_cube *cube, int y, int *player_count)
{
	int	x;

	x = 0;
	while (x < cube->maxx)
	{
		if (!is_valid_map_char(cube->map[y][x]))
			return (5);
		if (ft_strchr("NSWE", cube->map[y][x]))
			(*player_count)++;
		if (ft_strchr("0NSWE", cube->map[y][x]))
		{
			if (!is_enclosed(cube, y, x))
				return (6);
		}
		x++;
	}
	return (0);
}

int	validate_map(t_cube *cube)
{
	int	y;
	int	player_count;
	int	row_status;

	if (convert_list_to_array(cube) != 0)
		return (1);
	y = 0;
	player_count = 0;
	while (y < cube->maxy)
	{
		row_status = validate_map_row(cube, y, &player_count);
		if (row_status != 0)
			return (row_status);
		y++;
	}
	if (player_count != 1)
		return (7);
	return (0);
}
