#include "../cub3d.h"

static void	init_camera_ray(t_player *player, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / WINDOW_WIDTH - 1.0;
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
}

static void	calc_draw_limits(t_ray *ray, t_draw *draw)
{
	draw->height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	draw->start = -draw->height / 2 + WINDOW_HEIGHT / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->height / 2 + WINDOW_HEIGHT / 2;
	if (draw->end >= WINDOW_HEIGHT)
		draw->end = WINDOW_HEIGHT - 1;
}

static int	calc_tex_x(t_ray *ray, t_texture *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->hit_side == 0)
		wall_x = ray->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = ray->pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (ray->hit_side == 0 && ray->dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->hit_side == 1 && ray->dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_column(t_data *data, t_ray *ray,
		t_texture *tex, t_draw *draw)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	tex_x = calc_tex_x(ray, tex);
	step = 1.0 * tex->height / draw->height;
	tex_pos = (draw->start - WINDOW_HEIGHT / 2
			+ draw->height / 2) * step;
	y = 0;
	while (y < draw->start)
		my_mlx_pixel_put(&data->mlx.img, draw->x, y++,
			data->ceiling_color);
	while (y <= draw->end)
	{
		tex_y = (int)tex_pos % tex->height;
		tex_pos += step;
		my_mlx_pixel_put(&data->mlx.img, draw->x, y++,
			tex_pixel(tex, tex_x, tex_y));
	}
	while (y < WINDOW_HEIGHT)
		my_mlx_pixel_put(&data->mlx.img, draw->x, y++,
			data->floor_color);
}

void	cast_rays(t_data *data, t_player *player)
{
	t_ray		ray;
	t_draw		draw;
	t_texture	*tex;

	draw.x = 0;
	while (draw.x < WINDOW_WIDTH)
	{
		init_camera_ray(player, &ray, draw.x);
		dda_alg(player, &ray, &data->map);
		dda_loop(&ray, &data->map);
		calc_draw_limits(&ray, &draw);
		tex = pick_texture(&data->textures, &ray);
		draw_column(data, &ray, tex, &draw);
		draw.x++;
	}
	mlx_put_image_to_window(data->mlx.ptr,
		data->mlx.win, data->mlx.img.ptr, 0, 0);
}
