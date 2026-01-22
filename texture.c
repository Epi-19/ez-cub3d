#include "cub3d.h"

int load_texture(void *mlx_ptr, t_texture *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(mlx_ptr, path, &tex->width, &tex->height);
    if (!tex->img)
        return (0);
    tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel, &tex->line_length,&tex->endian);
    return (1);
}

int load_all_textures(void *mlx_ptr, t_textures *textures, t_map *map)
{
    if (!load_texture(mlx_ptr, &textures->north, map->north_tex_path))
        return (0);
    if (!load_texture(mlx_ptr, &textures->south, map->south_tex_path))
        return (0);
    if (!load_texture(mlx_ptr, &textures->east, map->east_tex_path))
        return (0);
    if (!load_texture(mlx_ptr, &textures->west, map->west_tex_path))
        return (0);
    return (1);
}

