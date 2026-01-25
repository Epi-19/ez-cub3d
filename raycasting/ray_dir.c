
#include "../cub3d.h"

void	player_dir_to_vector(t_player *player, t_ray *ray)
{
	if (player->direction == 'N')
	{
		ray->dir_x = 0;
		ray->dir_y = -1;
	}
	else if (player->direction == 'S')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
	}
	else if (player->direction == 'E')
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
	}
	else if (player->direction == 'W')
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
	}
}

void	init_camera_ray(t_player *player, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / WINDOW_WIDTH - 1.0;
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
}
