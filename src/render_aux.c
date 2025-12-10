/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:41:06 by dgasco-g          #+#    #+#             */
/*   Updated: 2025/11/25 17:21:44 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_texture_info(t_ray *ray, t_tex_info *tex_info)
{
	tex_info->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	tex_info->draw_start = -tex_info->line_height / 2 + SCREEN_HEIGHT / 2;
	if (tex_info->draw_start < 0)
		tex_info->draw_start = 0;
	tex_info->draw_end = tex_info->line_height / 2 + SCREEN_HEIGHT / 2;
	if (tex_info->draw_end >= SCREEN_HEIGHT)
		tex_info->draw_end = SCREEN_HEIGHT - 1;
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			tex_info->tex_num = 3;
		else
			tex_info->tex_num = 2;
	}
	else
	{
		if (ray->step_y > 0)
			tex_info->tex_num = 1;
		else
			tex_info->tex_num = 0;
	}
}

void	my_mlx_pixel_put(t_textures *img, int x, int y, int color)
{
	int	*pixels;

	pixels = (int *)img->addr;
	pixels[y * SCREEN_WIDTH + x] = color;
}

int	get_texture_color(t_textures *texture, int x, int y)
{
	int	*texture_pixels;

	if (!texture->addr)
		return (0xFF0000FF);
	texture_pixels = (int *)texture->addr;
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0x00FF00FF);
	return (texture_pixels[y * texture->width + x]);
}

void	init_ray(t_cube *cube, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = cube->player->camerax + cube->player->plane_x
		* ray->camera_x;
	ray->ray_dir_y = cube->player->cameray + cube->player->plane_y
		* ray->camera_x;
	ray->map_x = (int)cube->player->player_x;
	ray->map_y = (int)cube->player->player_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	calculate_texture_x(t_ray *ray, t_tex_info *tex_info, t_cube *cube,
		t_textures *tex)
{
	double	wall_hit;

	if (ray->side == 0)
		wall_hit = cube->player->player_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		wall_hit = cube->player->player_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	tex_info->wall_x = wall_hit - floor(wall_hit);
	tex_info->tex_x = (int)(tex_info->wall_x * tex->width);
}
