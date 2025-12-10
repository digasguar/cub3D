/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiahidal <oiahidal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 00:44:14 by oiahidal          #+#    #+#             */
/*   Updated: 2025/11/21 23:59:30 by oiahidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_tmap(t_tmap *map_list)
{
	t_tmap	*current;
	t_tmap	*next;

	current = map_list;
	while (current)
	{
		next = current->next;
		free(current->raw_line);
		free(current->line);
		free(current);
		current = next;
	}
}

static void	print_error_message(int error)
{
	ft_putstr_fd("Error\n", 2);
	if (error == 1)
		ft_putstr_fd("Invalid arguments. Usage: ./cub3D <map.cub>\n", 2);
	else if (error == 2)
		ft_putstr_fd("Invalid file extension. Map must be '.cub'\n", 2);
	else if (error == 3)
		ft_putstr_fd("Could not open map file.\n", 2);
	else if (error == 4)
		ft_putstr_fd("File error: Invalid, duplicate, or malformed ids.\n", 2);
	else if (error == 5)
		ft_putstr_fd("Map error: Invalid format or characters.\n", 2);
	else if (error == 6)
		ft_putstr_fd("Map error: Map is not enclosed by walls.\n", 2);
	else if (error == 7)
		ft_putstr_fd("Map error: Must be exactly 1 player (N, S, E, W).\n", 2);
	else if (error == 8)
		ft_putstr_fd("Memory allocation error.\n", 2);
	else if (error == 9)
		ft_putstr_fd("Texture must be a '.xpm'.\n", 2);
	else
		ft_putstr_fd("An unknown parsing error occurred.\n", 2);
}

void	free_parse_data(t_cube *cube)
{
	if (!cube)
		return ;
	if (cube->map_fd > 2)
		close(cube->map_fd);
	if (cube->ntex)
		free(cube->ntex);
	if (cube->stex)
		free(cube->stex);
	if (cube->wtex)
		free(cube->wtex);
	if (cube->etex)
		free(cube->etex);
	if (cube->temp_map)
		free_tmap(cube->temp_map);
	if (cube->ids)
		free(cube->ids);
	if (cube->map)
		free_array(cube->map);
	free(cube);
}

void	exit_error(int error, t_cube *cube)
{
	print_error_message(error);
	free_parse_data(cube);
	exit(1);
}
