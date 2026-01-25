#include "../cub3d.h"

void	init_ray_pos(t_player *player, t_ray *ray)
{
	ray->pos_x = player->x;
	ray->pos_y = player->y;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
}

void	init_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->dist_next_vert = 2147483647;
	else
		ray->dist_next_vert = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->dist_next_horiz = 2147483647;
	else
		ray->dist_next_horiz = fabs(1 / ray->dir_y);
}

void	init_step_x(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->dist_vert_border = (ray->pos_x - ray->map_x)
			* ray->dist_next_vert;
	}
	else
	{
		ray->step_x = 1;
		ray->dist_vert_border = (ray->map_x + 1.0 - ray->pos_x)
			* ray->dist_next_vert;
	}
}

void	init_step_y(t_ray *ray)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->dist_horiz_border = (ray->pos_y - ray->map_y)
			* ray->dist_next_horiz;
	}
	else
	{
		ray->step_y = 1;
		ray->dist_horiz_border = (ray->map_y + 1.0 - ray->pos_y)
			* ray->dist_next_horiz;
	}
}

void	dda_alg(t_player *player, t_ray *ray, t_map *map)
{
	(void)map;
	init_ray_pos(player, ray);
	init_delta_dist(ray);
	init_step_x(ray);
	init_step_y(ray);
}
