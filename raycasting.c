#define MAP_W 6
#define MAP_H 5
#include "cub3d.h"

int map[MAP_H][MAP_W] = {
    {1,1,1,1,1,1},
    {1,0,0,0,0,1},
    {1,0,0,0,0,1},
    {1,0,0,0,0,1},
    {1,1,1,1,1,1}
};

void player_dir_to_vector(t_player *player, t_ray *ray)
{
    if (player->direction == 'N') {
        ray->dirX = 0;
        ray->dirY = -1;
    } else if (player->direction == 'S') {
        ray->dirX = 0;
        ray->dirY = 1;
    } else if (player->direction == 'E') {
        ray->dirX = 1;
        ray->dirY = 0;
    } else if (player->direction == 'W') {
        ray->dirX = -1;
        ray->dirY = 0;
    }
}

void dda_alg(t_player *player, t_ray *ray, t_map *map)
{
    ray->posX = player->x;
    ray->posY = player->y;
    player_dir_to_vector(player, ray);
    ray->mapX = (int)ray->posX;
    ray->mapY = (int)ray->posY;
    if (ray->dirX == 0)
        ray->distToNextVertical = 2147483647;
    else
        ray->distToNextVertical = fabs(1 / ray->dirX);

    if (ray->dirY == 0)
        ray->distToNextHorizontal = 2147483647;
    else
        ray->distToNextHorizontal = fabs(1 / ray->dirY);
    if (ray->dirX < 0)
    {
        ray->stepX = -1;
        ray->distToVerticalBorder = (ray->posX - ray->mapX) * ray->distToNextVertical;
    }
    else
    {
        ray->stepX = 1;
        ray->distToVerticalBorder = (ray->mapX + 1.0 - ray->posX) * ray->distToNextVertical;
    }

    if (ray->dirY < 0)
    {
        ray->stepY = -1;
        ray->distToHorizontalBorder = (ray->posY - ray->mapY) * ray->distToNextHorizontal;
    }
    else
    {
        ray->stepY = 1;
        ray->distToHorizontalBorder = (ray->mapY + 1.0 - ray->posY) * ray->distToNextHorizontal;
    }
}

