/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgasco-g <dgasco-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 08:51:55 by dgasco-g          #+#    #+#             */
/*   Updated: 2025/11/25 17:23:38 by dgasco-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define PLAYER_SPEED 0.1
# define CAMERA_SPEED 0.05
# define COLLISION 0.2
# define SCREEN_WIDTH 1240
# define SCREEN_HEIGHT 880

typedef struct s_player
{
	double			player_y;
	double			player_x;
	double			camerax;
	double			cameray;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_ids
{
	int				count_ids;
	int				map_ids;
	bool			no;
	bool			so;
	bool			we;
	bool			ea;
	bool			f;
	bool			c;

}					t_ids;

typedef struct s_tmap
{
	char			*raw_line;
	char			*line;
	int				len;
	struct s_tmap	*next;

}					t_tmap;

typedef struct s_textures
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;

}					t_textures;

typedef struct s_hook
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				right;
	int				left;
}					t_hook;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
}					t_ray;

typedef struct s_tex_info
{
	int				tex_num;
	double			wall_x;
	int				tex_x;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_tex_info;

typedef struct s_cube
{
	char			**map;

	void			*mlx_window;
	void			*mlx;

	int				hiden_mouse;
	char			*ntex;
	char			*stex;
	char			*wtex;
	char			*etex;

	int				fcolor[3];
	int				ccolor[3];
	int				maxy;
	int				maxx;
	char			*map_path;
	int				map_fd;
	char			*raw_map;
	t_tmap			*temp_map;
	t_ids			*ids;
	t_player		*player;
	t_textures		textures[4];
	t_textures		*img;
	t_hook			*hooks;
	int				mouse_y;
	int				mouse_x;
	int				pos_y;
	int				pos_x;
	int				screen_y;
	int				screen_x;
}					t_cube;

// IDs: 1 = NO | 2 = SO | 3 = WE | 4 = EA | 5 = F | 6 = C

// Funciones
int					render(t_cube *cube);
int					load_textures(t_cube *cube);
void				init_player(t_cube *cube);
// int		key_hook(int keycode, t_cube *cube);
int					game_loop(t_cube *cube);
int					close_game(t_cube *data);

//---------------------------------------------------------------------movements
void				move_camera(int keycode, t_cube *cube);
int					keyprees(int keycode, t_cube *cube);
int					keyrelease(int keycode, t_cube *cube);
void				move_up(t_cube *cube);
void				move_down(t_cube *cube);
void				move_left(t_cube *cube);
void				move_right(t_cube *cube);
void				move_player(t_cube *cube);
void				my_mlx_pixel_put(t_textures *img, int x, int y, int color);
//-------------------------------------------------------------------
void				move_camera(int keycode, t_cube *cube);
void				init_data(t_cube *cube, char *map_file);
void				free_textures(t_cube *data);
void				clean_data(t_cube *data);
int					parse_file(t_cube *cube, int fd);
int					validate_map(t_cube *cube);
t_tmap				*tmap_new(char *raw_line);
void				tmap_add_back(t_tmap **lst, t_tmap *new_node);
int					normalize_map_lines(t_tmap **map);
void				exit_error(int error, t_cube *cube);
void				free_tmap(t_tmap *map_list);
int					is_valid_args(int argc, char **args, t_cube *cube);
int					ft_strcmp(const char *s1, const char *s2);
int					is_valid_color_string(char *str);
void				free_parse_data(t_cube *cube);
void				draw_map(t_cube *c);
void				calculate_wall_distance(t_cube *cube, t_ray *ray);
void				draw_textured_wall(t_cube *cube, t_tex_info *info, int x);
void				get_texture_info(t_ray *ray, t_tex_info *tex_info);
int					get_texture_color(t_textures *texture, int x, int y);
void				init_ray(t_cube *cube, t_ray *ray, int x);
void				calculate_texture_x(t_ray *ray, t_tex_info *tex_info,
						t_cube *cube, t_textures *tex);
int					mouse_move(int x, int y, t_cube *cube);
int					init_substructs(t_cube *cube);
int					check_textures(t_cube *cube);

#endif
