#include "cub3d.h"
//moncode
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
    (void)map;
    ray->posX = player->x;
    ray->posY = player->y;
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

void dda_loop(t_ray *ray, t_map *map)
{
    int border;
    double perpWallDist;

    while (1)
    {
        if (ray->distToVerticalBorder < ray->distToHorizontalBorder)
        {
            ray->distToVerticalBorder += ray->distToNextVertical;
            ray->mapX += ray->stepX;
            border = 0;
        }
        else
        {
            ray->distToHorizontalBorder += ray->distToNextHorizontal;
            ray->mapY += ray->stepY;
            border = 1;
        }
        if (ray->mapY >= 0 && ray->mapY < map->height 
            && ray->mapX >= 0 && ray->mapX < map->width)
        {
            if (map->grid[ray->mapY][ray->mapX] == '1')
                break;
        }
        else
            break;
    }
    ray->hitSide = border;
    if (border == 0)
        perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX) / 2) / ray->dirX;
    else
        perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2) / ray->dirY;
    ray->perpWallDist = perpWallDist;
}
//moncode

static t_texture *pick_texture(t_textures *tex, t_ray *ray)
{
    if (ray->hitSide == 0)
    {
        if (ray->dirX > 0)
            return (&tex->east);
        return (&tex->west);
    }
    if (ray->dirY > 0)
        return (&tex->south);
    return (&tex->north);
}

static int tex_pixel(t_texture *tex, int x, int y)
{
    char *ptr;

    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0);
    ptr = tex->addr + y * tex->line_length + x * (tex->bits_per_pixel / 8);
    return (*(unsigned int *)ptr);
}

void cast_rays(t_data *data, t_player *player)
{
    int x;
    t_ray ray;
    double cameraX;
    int lineHeight;
    int drawStart;
    int drawEnd;
    int y;
    t_texture *tex;
    double wallX;
    int texX;
    double step;
    double texPos;

    x = 0;
    while (x < WINDOW_WIDTH)
    {
        cameraX = 2.0 * x / WINDOW_WIDTH - 1.0;
        ray.dirX = player->dirX + player->planeX * cameraX;
        ray.dirY = player->dirY + player->planeY * cameraX;

        dda_alg(player, &ray, &data->map);
        dda_loop(&ray, &data->map);

        lineHeight = (int)(WINDOW_HEIGHT / ray.perpWallDist);
        drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
        if (drawEnd >= WINDOW_HEIGHT)
            drawEnd = WINDOW_HEIGHT - 1;

        tex = pick_texture(&data->textures, &ray);
        if (ray.hitSide == 0)
            wallX = ray.posY + ray.perpWallDist * ray.dirY;
        else
            wallX = ray.posX + ray.perpWallDist * ray.dirX;
        wallX -= floor(wallX);
        texX = (int)(wallX * tex->width);
        if (ray.hitSide == 0 && ray.dirX > 0)
            texX = tex->width - texX - 1;
        if (ray.hitSide == 1 && ray.dirY < 0)
            texX = tex->width - texX - 1;
        step = 1.0 * tex->height / lineHeight;
        texPos = (drawStart - WINDOW_HEIGHT / 2 + lineHeight / 2) * step;

        y = 0;
        while (y < drawStart)
            my_mlx_pixel_put(&data->mlx.img, x, y++, data->ceiling_color);
        while (y <= drawEnd)
        {
            int texY = (int)texPos % tex->height;
            texPos += step;
            int color = tex_pixel(tex, texX, texY);
            my_mlx_pixel_put(&data->mlx.img, x, y++, color);
        }
        while (y < WINDOW_HEIGHT)
            my_mlx_pixel_put(&data->mlx.img, x, y++, data->floor_color);
        x++;
    }
    mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.img.ptr, 0, 0);
}
