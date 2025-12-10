/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 05:04:29 by dgasco-g          #+#    #+#             */
/*   Updated: 2025/11/25 16:03:10 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	calculate_step_and_side_dist(t_cube *cube, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cube->player->player_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cube->player->player_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cube->player->player_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cube->player->player_y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_cube *cube, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= cube->maxy || ray->map_x < 0
			|| ray->map_x >= cube->maxx)
			ray->hit = 1;
		else if (cube->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	draw_floor_and_ceiling(t_cube *cube, t_tex_info *tex_info, int x)
{
	int	y;
	int	ceil_color;
	int	floor_color;

	ceil_color = (cube->ccolor[0] << 16) | \
	(cube->ccolor[1] << 8) | cube->ccolor[2];
	floor_color = (cube->fcolor[0] << 16) | \
	(cube->fcolor[1] << 8) | cube->fcolor[2];
	y = 0;
	while (y < tex_info->draw_start)
		my_mlx_pixel_put(cube->img, x, y++, ceil_color);
	y = tex_info->draw_end;
	while (y < SCREEN_HEIGHT)
		my_mlx_pixel_put(cube->img, x, y++, floor_color);
}

static void	render_column(t_cube *cube, int x)
{
	t_ray		ray;
	t_tex_info	tex_info;
	t_textures	*tex;

	init_ray(cube, &ray, x);
	calculate_step_and_side_dist(cube, &ray);
	perform_dda(cube, &ray);
	calculate_wall_distance(cube, &ray);
	get_texture_info(&ray, &tex_info);
	tex = &cube->textures[tex_info.tex_num];
	calculate_texture_x(&ray, &tex_info, cube, tex);
	draw_floor_and_ceiling(cube, &tex_info, x);
	draw_textured_wall(cube, &tex_info, x);
}

int	render(t_cube *cube)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		render_column(cube, x);
		x++;
	}
	mlx_put_image_to_window(cube->mlx, cube->mlx_window, cube->img->img, 0, 0);
	return (0);
}
