#include "cub3d.h"


int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}


int main(int argc, char **argv)
{
    t_data      data;
    const char  *map_path;

    ft_memset(&data, 0, sizeof(t_data));
    data.floor_color = -1;
    data.ceiling_color = -1;

    // --- Init MLX ---
    if (init_mlx(&data.mlx) != 0)
        return (1);

    map_path = (argc >= 2) ? argv[1] : "maps/simple_test.cub";
    if (load_map(map_path, &data) != 0)
    {
        destroy_mlx(&data.mlx);
        return (1);
    }

    if (!data.map.north_tex_path || !data.map.south_tex_path
        || !data.map.east_tex_path || !data.map.west_tex_path)
    {
        printf("Error: texture identifiers missing in %s\n", map_path);
        destroy_mlx(&data.mlx);
        return (1);
    }

    if (load_all_textures(data.mlx.ptr, &data.textures, &data.map) == 0)
    {
        destroy_mlx(&data.mlx);
        return (1);
    }

    if (data.floor_color == -1)
        data.floor_color = 0x404040;
    if (data.ceiling_color == -1)
        data.ceiling_color = 0x87CEEB;

    // --- Player ---
    player_pos_dir(&data.map, &data.player);
    init_player_plane(&data.player);

    // --- Hooks ---
    mlx_hook(data.mlx.win, 17, 0, close_window, &data);
    mlx_hook(data.mlx.win, 2, 1L<<0, key_press, &data);    // KeyPress
    mlx_hook(data.mlx.win, 3, 1L<<1, key_release, &data);  // KeyRelease
    mlx_loop_hook(data.mlx.ptr, moves, &data);            // Boucle frame

    // --- Boucle MLX ---
    mlx_loop(data.mlx.ptr);

    return (0);
}
