/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiahidal <oiahidal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 09:10:45 by oiahidal          #+#    #+#             */
/*   Updated: 2025/11/25 14:16:30 by oiahidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	set_id_flag(t_ids *ids, int id_type)
{
	if (id_type == 1)
		ids->no = true;
	else if (id_type == 2)
		ids->so = true;
	else if (id_type == 3)
		ids->we = true;
	else if (id_type == 4)
		ids->ea = true;
	else if (id_type == 5)
		ids->f = true;
	else if (id_type == 6)
		ids->c = true;
}

static int	validate_and_store(t_cube *cube, char **tokens)
{
	int	id_type;
	int	status;

	id_type = is_valid_id(cube->ids, tokens[0]);
	if (id_type == 0)
		return (-1);
	status = 1;
	if (id_type >= 1 && id_type <= 4)
		status = store_texture(cube, tokens, id_type);
	else if (id_type >= 5 && id_type <= 6)
		status = store_color(cube, tokens, id_type);
	if (status != 0)
		return (-1);
	set_id_flag(cube->ids, id_type);
	cube->ids->count_ids++;
	return (0);
}

static int	process_identifier_line(t_cube *cube, char *line)
{
	char	**tokens;
	char	*trimmed_line;
	int		status;

	trimmed_line = ft_strtrim(line, " \t\n");
	if (!trimmed_line)
		return (-1);
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (1);
	}
	tokens = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!tokens || !tokens[0])
	{
		free_tokens(tokens);
		return (-1);
	}
	status = validate_and_store(cube, tokens);
	free_tokens(tokens);
	return (status);
}

static int	process_map_line(t_cube *cube, char *line, bool *map_started)
{
	t_tmap	*new_node;
	char	*trimmed_line;
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if ((line[i] == '\n' || line[i] == '\0') && *map_started == false)
		return (0);
	*map_started = true;
	if ((line[i] == '\n' || line[i] == '\0') && *map_started == true)
		return (1);
	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
		return (1);
	new_node = tmap_new(trimmed_line);
	free(trimmed_line);
	if (!new_node)
		return (1);
	tmap_add_back(&cube->temp_map, new_node);
	return (0);
}

int	parse_file(t_cube *cube, int fd)
{
	char	*line;
	int		status;
	bool	map_started;

	map_started = false;
	ft_memset(cube->ids, 0, sizeof(t_ids));
	line = get_next_line(fd);
	while (line)
	{
		if (cube->ids->count_ids < 6)
			status = process_identifier_line(cube, line);
		else
			status = process_map_line(cube, line, &map_started);
		free(line);
		if (status == -1 || (status == 1 && cube->ids->count_ids == 6))
			return (1);
		line = get_next_line(fd);
	}
	if (cube->ids->count_ids < 6)
		return (1);
	if (!cube->temp_map)
		return (1);
	return (0);
}
