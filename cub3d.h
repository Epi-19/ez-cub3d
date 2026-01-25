/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 02:23:39 by rodebacq          #+#    #+#             */
/*   Updated: 2026/01/21 22:10:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# define WINDOW_WIDTH       1200
# define WINDOW_HEIGHT      800

# define ESC_KEY            65307
# define KEY_W              119
# define KEY_A              97
# define KEY_S              115
# define KEY_D              100
# define KEY_LEFT           65363
# define KEY_RIGHT          65361

# define MOVE_SPEED         0.01
# define ROT_SPEED          0.01

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*north_tex_path;
	char	*south_tex_path;
	char	*east_tex_path;
	char	*west_tex_path;
}	t_map;
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}	t_textures;
typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	img;
}	t_mlx;

typedef struct s_player
{
	double	x;
	double	y;
	char	direction;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_data
{
	t_mlx		mlx;
	t_map		map;
	t_textures	textures;
	t_player	player;
	int			floor_color;
	int			ceiling_color;
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_left;
	int			key_right;
}	t_data;

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	dist_next_vert;
	double	dist_next_horiz;
	double	dist_vert_border;
	double	dist_horiz_border;
	double	perp_wall_dist;
	int		hit_side;
}	t_ray;

typedef struct s_draw
{
	int	start;
	int	end;
	int	height;
	int	x;
}	t_draw;

int			init_mlx(t_mlx *mlx);
void		destroy_mlx(t_mlx *mlx);
int			load_map(const char *filename, t_data *data);
void		init_player_plane(t_player *player);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		cast_rays(t_data *data, t_player *player);
void		player_dir_to_vector(t_player *player, t_ray *ray);
void		player_pos_dir(t_map *map, t_player *player);
int			load_all_textures(void *mlx_ptr, t_textures *textures, t_map *map);
int			load_texture(void *mlx_ptr, t_texture *tex, char *path);
void		move_w(t_player *player, t_map *map);
int			moves(t_data *data);
int			key_release(int keycode, t_data *data);
int			key_press(int keycode, t_data *data);
void		rotate_left(t_player *player);
void		rotate_right(t_player *player);

void		init_ray_pos(t_player *player, t_ray *ray);
void		init_delta_dist(t_ray *ray);
void		init_step_x(t_ray *ray);
void		init_step_y(t_ray *ray);
void		dda_alg(t_player *player, t_ray *ray, t_map *map);
int			step_dda(t_ray *ray);
int			is_wall_hit(t_ray *ray, t_map *map);
void		calc_perp_wall_dist(t_ray *ray);
void		dda_loop(t_ray *ray, t_map *map);
void		init_ray_dir(t_ray *ray, t_player *player, int x);
t_texture	*pick_texture(t_textures *tex, t_ray *ray);
int			tex_pixel(t_texture *tex, int x, int y);
void		move_d(t_player *player, t_map *map) ;
void		move_a(t_player *player, t_map *map) ;
void		move_s(t_player *player, t_map *map) ;
void		move_w(t_player *player, t_map *map) ;
#endif