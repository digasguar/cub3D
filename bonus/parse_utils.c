/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiahidal <oiahidal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:26:29 by oiahidal          #+#    #+#             */
/*   Updated: 2025/11/21 23:57:47 by oiahidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_tmap	*tmap_new(char *raw_line)
{
	t_tmap	*new_node;

	if (!raw_line)
		return (NULL);
	new_node = (t_tmap *)malloc(sizeof(t_tmap));
	if (!new_node)
		return (NULL);
	new_node->raw_line = ft_strdup(raw_line);
	if (!new_node->raw_line)
	{
		free(new_node);
		return (NULL);
	}
	new_node->line = NULL;
	new_node->len = ft_strlen(new_node->raw_line);
	new_node->next = NULL;
	return (new_node);
}

void	tmap_add_back(t_tmap **lst, t_tmap *new_node)
{
	t_tmap	*current;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

static int	get_max_width(t_tmap *map)
{
	int		max_width;
	t_tmap	*current;

	max_width = 0;
	current = map;
	while (current)
	{
		if (current->len > max_width)
			max_width = current->len;
		current = current->next;
	}
	return (max_width);
}

static char	*create_padded_line(const char *raw_line, int len, int max_width)
{
	char	*new_line;
	int		i;

	new_line = (char *)malloc(sizeof(char) * (max_width + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_line[i] = raw_line[i];
		i++;
	}
	while (i < max_width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

int	normalize_map_lines(t_tmap **map)
{
	int		max_width;
	t_tmap	*current;

	if (!map || !*map)
		return (0);
	max_width = get_max_width(*map);
	current = *map;
	while (current)
	{
		free(current->line);
		current->line = create_padded_line(current->raw_line, \
			current->len, max_width);
		if (!current->line)
			return (1);
		current = current->next;
	}
	return (0);
}
