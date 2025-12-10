/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:27:39 by oiahidal          #+#    #+#             */
/*   Updated: 2025/11/25 17:21:58 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	extension_check(char *s1)
{
	char	*str;
	int		error;

	str = ft_strrchr(s1, '.');
	error = ft_strcmp(str, ".xpm\0");
	if (error)
		return (9);
	return (0);
}

int	check_textures(t_cube *cube)
{
	int	error;

	error = extension_check(cube->ntex);
	if (error)
		return (9);
	error = extension_check(cube->stex);
	if (error)
		return (9);
	error = extension_check(cube->etex);
	if (error)
		return (9);
	error = extension_check(cube->wtex);
	if (error)
		return (9);
	return (0);
}

static int	file_exist(char *path, t_cube *cube)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	cube->map_path = path;
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

int	is_valid_args(int argc, char **args, t_cube *cube)
{
	char	*str;

	if (argc < 2 || argc > 2)
		return (1);
	str = ft_strrchr(args[1], '.');
	if (!str)
		return (2);
	if (ft_strcmp(str, ".cub"))
		return (2);
	if (file_exist(args[1], cube))
		return (3);
	return (0);
}
