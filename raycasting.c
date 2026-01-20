#define MAP_W 6
#define MAP_H 5
#include "cub3d"

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
void init_ray(t_player *player, t_ray *ray, t_map *map)
{
    int step = 0.05;

    player_dir_to_vector(player, ray);
    while(1)
    {
        if(player->direction == 'N')
        {
            ray->dirX += 0;
            ray->dirY += -step;
        }
        else if(player->direction == 'E')
        {
            ray->dirX += step;
            ray->dirY += 0;
        }
        else if(player->direction == 'S')
        {
            ray->dirX += 0;
            ray->dirY += step;
        }
        else if(player->direction == 'W')
        {
            ray->dirX += -step;
            ray->dirY += 0;
        }
        map.width = (int)(ray->dirX);
        map.height = (int)(ray->dirY);
        if(map.grid[map.height][map.width] == '1')
            break;
    }
}
