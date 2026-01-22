#include "cub3d.h"

void move_w(t_player *player,t_map *map)
{
    double newX ;
    double newY ;

    newX = player->x + player->dirX * MOVE_SPEED ;
    newY = player->y + player->dirY * MOVE_SPEED ;
    if(map->grid[(int)player->y][(int)newX] != '1')
        player->x = newX ;
    if(map->grid[(int)newY][(int)player->x] != '1')
        player->y = newY ;
}