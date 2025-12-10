/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 08:50:18 by dgasco-g          #+#    #+#             */
/*   Updated: 2025/11/25 16:03:10 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	set_color(char c)
{
	int	color;

	if (c == '1')
		color = 0xFFFFFF;
	else if (c == '2')
		color = 0xFF00FF;
	else
		color = 0x000000;
	return (color);
}

static void	draw_pixels_map(t_cube *cube, int screen_y, int screen_x, char c)
{
	int	end_y;
	int	end_x;
	int	color;

	end_y = screen_y + 8;
	end_x = screen_x + 8;
	color = set_color(c);
	while (screen_y < end_y)
	{
		screen_y++;
		if (screen_y % 2 == 0)
			continue ;
		screen_x = end_x - 8;
		while (screen_x < end_x)
		{
			screen_x++;
			if (screen_x % 2 == 0)
				continue ;
			my_mlx_pixel_put(cube->img, screen_x, screen_y, color);
		}
	}
}

static void	draw_aux(t_cube *c, int map_x, int map_y)
{
	if (map_y < 0 || map_y >= c->maxy || map_x < 0
		|| map_x >= c->maxx)
		draw_pixels_map(c, c->screen_y, c->screen_x, '0');
	else if (c->pos_x == 0 && c->pos_y == 0)
		draw_pixels_map(c, c->screen_y, c->screen_x, '2');
	else
		draw_pixels_map(c, c->screen_y, c->screen_x, c->map[map_y][map_x]);
}

void	draw_map(t_cube *c)
{
	int	map_y;
	int	map_x;

	c->screen_y = 10;
	c->pos_y = -15;
	while (c->pos_y <= 15)
	{
		c->screen_x = 10;
		c->pos_x = -15;
		map_y = (int)c->player->player_y + c->pos_y;
		while (c->pos_x <= 15)
		{
			map_x = (int)c->player->player_x + c->pos_x;
			draw_aux(c, map_x, map_y);
			c->screen_x += 8;
			c->pos_x++;
		}
		c->screen_y += 8;
		c->pos_y++;
	}
}
