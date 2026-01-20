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