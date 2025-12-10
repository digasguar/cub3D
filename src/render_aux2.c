/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:47:10 by dgasco-g          #+#    #+#             */
/*   Updated: 2025/11/25 15:59:05 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_textured_wall(t_cube *cube, t_tex_info *info, int x)
{
	t_textures	*tex;
	double		step;
	double		tex_pos;
	int			y;

	tex = &cube->textures[info->tex_num];
	step = (double)tex->height / info->line_height;
	tex_pos = (info->draw_start - SCREEN_HEIGHT / 2 + info->line_height / 2)
		* step;
	y = info->draw_start;
	while (y < info->draw_end)
	{
		tex_pos += step;
		my_mlx_pixel_put(cube->img, x, y, get_texture_color(tex, info->tex_x,
				(int)tex_pos & (tex->height - 1)));
		y++;
	}
}

void	calculate_wall_distance(t_cube *cube, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - cube->player->player_x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - cube->player->player_y + (1
					- ray->step_y) / 2) / ray->ray_dir_y;
}
