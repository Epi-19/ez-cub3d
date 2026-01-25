
#include "../cub3d.h"

void	move_w(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->x + player->dir_x * MOVE_SPEED;
	new_y = player->y + player->dir_y * MOVE_SPEED;
	if (map->grid[(int)player->y][(int)(new_x + player->dir_x * 0.5)] != '1')
		player->x = new_x;
	if (map->grid[(int)(new_y + player->dir_y * 0.5)][(int)player->x] != '1')
		player->y = new_y;
}

void	move_s(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->x - player->dir_x * MOVE_SPEED;
	new_y = player->y - player->dir_y * MOVE_SPEED;
	if (map->grid[(int)player->y][(int)(new_x - player->dir_x * 0.5)] != '1')
		player->x = new_x;
	if (map->grid[(int)(new_y - player->dir_y * 0.5)][(int)player->x] != '1')
		player->y = new_y;
}

void	move_a(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->x - player->dir_y * MOVE_SPEED;
	new_y = player->y + player->dir_x * MOVE_SPEED;
	if (map->grid[(int)player->y][(int)(new_x - player->dir_y * 0.5)] != '1')
		player->x = new_x;
	if (map->grid[(int)(new_y + player->dir_x * 0.5)][(int)player->x] != '1')
		player->y = new_y;
}

void	move_d(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->x + player->dir_y * MOVE_SPEED;
	new_y = player->y - player->dir_x * MOVE_SPEED;
	if (map->grid[(int)player->y][(int)(new_x + player->dir_y * 0.5)] != '1')
		player->x = new_x;
	if (map->grid[(int)(new_y - player->dir_x * 0.5)][(int)player->x] != '1')
		player->y = new_y;
}
