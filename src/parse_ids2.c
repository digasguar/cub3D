/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ids2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 23:53:00 by oiahidal          #+#    #+#             */
/*   Updated: 2025/11/25 16:02:28 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	is_valid_id(t_ids *ids, char *token)
{
	if (!ft_strcmp(token, "NO") && !ids->no)
		return (1);
	if (!ft_strcmp(token, "SO") && !ids->so)
		return (2);
	if (!ft_strcmp(token, "WE") && !ids->we)
		return (3);
	if (!ft_strcmp(token, "EA") && !ids->ea)
		return (4);
	if (!ft_strcmp(token, "F") && !ids->f)
		return (5);
	if (!ft_strcmp(token, "C") && !ids->c)
		return (6);
	return (0);
}

int	store_texture(t_cube *cube, char **tokens, int id)
{
	char	*path;

	if (tokens[2] != NULL || !tokens[1])
		return (1);
	path = ft_strdup(tokens[1]);
	if (!path)
		return (1);
	if (id == 1)
		cube->ntex = path;
	else if (id == 2)
		cube->stex = path;
	else if (id == 3)
		cube->wtex = path;
	else if (id == 4)
		cube->etex = path;
	else
		free(path);
	return (0);
}

int	store_color(t_cube *cube, char **tokens, int id)
{
	char	**rgb;
	int		*colors;
	int		i;

	if (tokens[2] || !tokens[1])
		return (1);
	rgb = ft_split(tokens[1], ',');
	if (!rgb)
		return (1);
	colors = cube->ccolor;
	if (id == 5)
		colors = cube->fcolor;
	i = -1;
	while (++i < 3)
	{
		if (!rgb[i] || !is_valid_color_string(rgb[i]) || \
			ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (free_tokens(rgb), 1);
		colors[i] = ft_atoi(rgb[i]);
	}
	if (rgb[i])
		return (free_tokens(rgb), 1);
	return (free_tokens(rgb), 0);
}
