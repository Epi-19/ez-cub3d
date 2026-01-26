#include "../cub3d.h"

int	step_dda(t_ray *ray)
{
	int	border;

	if (ray->dist_vert_border < ray->dist_horiz_border)
	{
		ray->dist_vert_border += ray->dist_next_vert;
		ray->map_x += ray->step_x;
		border = 0;
	}
	else
	{
		ray->dist_horiz_border += ray->dist_next_horiz;
		ray->map_y += ray->step_y;
		border = 1;
	}
	return (border);
}

int	is_wall_hit(t_ray *ray, t_map *map)
{
	if (ray->map_y < 0 || ray->map_y >= map->height
		|| ray->map_x < 0 || ray->map_x >= map->width)
		return (1);
	if (map->grid[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

void	calc_perp_wall_dist(t_ray *ray)
{
	if (ray->hit_side == 0)
	{
		if (ray->dir_x != 0)
			ray->perp_wall_dist = (ray->map_x - ray->pos_x
					+ (1 - ray->step_x) / 2) / ray->dir_x;
		else
			ray->perp_wall_dist = 2147483647;
	}
	else
	{
		if (ray->dir_y != 0)
			ray->perp_wall_dist = (ray->map_y - ray->pos_y
					+ (1 - ray->step_y) / 2) / ray->dir_y;
		else
			ray->perp_wall_dist = 2147483647;
	}
	if (ray->perp_wall_dist < 0.1)
		ray->perp_wall_dist = 0.1;
}

void	dda_loop(t_ray *ray, t_map *map)
{
	int	border;

	while (1)
	{
		border = step_dda(ray);
		if (is_wall_hit(ray, map))
			break ;
	}
	ray->hit_side = border;
	calc_perp_wall_dist(ray);
}
