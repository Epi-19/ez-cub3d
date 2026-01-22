#include "cub3d.h"

void player_pos_dir(t_map *map, t_player *player)
{
    int i;
    int j;

    i = 0;
    while (i < map->height)
    {
        j = 0;
        while (j < map->width)
        {
            if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' ||
                map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
                {
                    player->x = j;
                    player->y = i;
                    player->direction = map->grid[i][j];
                    return;
                }
            j++;
        }
        i++;
    }
}
void init_player_plane(t_player *player)
{
	if (player->direction == 'N')
	{
		player->dirX = 0; player->dirY = -1;
		player->planeX = 0.66; player->planeY = 0;
	}
	else if (player->direction == 'S')
	{
		player->dirX = 0; player->dirY = 1;
		player->planeX = -0.66; player->planeY = 0;
	}
	else if (player->direction == 'E')
	{
		player->dirX = 1; player->dirY = 0;
		player->planeX = 0; player->planeY = 0.66;
	}
	else if (player->direction == 'W')
	{
		player->dirX = -1; player->dirY = 0;
		player->planeX = 0; player->planeY = -0.66;
	}
}
