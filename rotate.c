#include "cub3d.h"
#include <math.h>

#define NECK_VELOCITY 2.0

void rotate_left(t_player *p)
{
    double oldDirX = p->dirX;
    double oldPlaneX = p->planeX;

    p->dirX = p->dirX * cos(ROT_SPEED) - p->dirY * sin(ROT_SPEED);
    p->dirY = oldDirX * sin(ROT_SPEED) + p->dirY * cos(ROT_SPEED);
    p->planeX = p->planeX * cos(ROT_SPEED) - p->planeY * sin(ROT_SPEED);
    p->planeY = oldPlaneX * sin(ROT_SPEED) + p->planeY * cos(ROT_SPEED);
}

void rotate_right(t_player *p)
{
    double oldDirX = p->dirX;
    double oldPlaneX = p->planeX;

    p->dirX = p->dirX * cos(-ROT_SPEED) - p->dirY * sin(-ROT_SPEED);
    p->dirY = oldDirX * sin(-ROT_SPEED) + p->dirY * cos(-ROT_SPEED);
    p->planeX = p->planeX * cos(-ROT_SPEED) - p->planeY * sin(-ROT_SPEED);
    p->planeY = oldPlaneX * sin(-ROT_SPEED) + p->planeY * cos(-ROT_SPEED);
}