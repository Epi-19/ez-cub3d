
#include "cub3d.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

static void	set_default_colors(t_data *data)
{
	if (data->floor_color == -1)
		data->floor_color = 0x404040;
	if (data->ceiling_color == -1)
		data->ceiling_color = 0x87CEEB;
}

static int	init_game(t_data *data, char *map_path)
{
	ft_memset(data, 0, sizeof(t_data));
	data->floor_color = -1;
	data->ceiling_color = -1;
	if (init_mlx(&data->mlx) != 0)
		return (1);
	if (load_map(map_path, data) != 0)
	{
		destroy_mlx(&data->mlx);
		return (1);
	}
	if (!data->map.north_tex_path || !data->map.south_tex_path
		|| !data->map.east_tex_path || !data->map.west_tex_path)
	{
		printf("Error: texture identifiers missing in %s\n", map_path);
		destroy_mlx(&data->mlx);
		return (1);
	}
	if (load_all_textures(data->mlx.ptr, &data->textures, &data->map) == 0)
		return (destroy_mlx(&data->mlx), 1);
	set_default_colors(data);
	player_pos_dir(&data->map, &data->player);
	init_player_plane(&data->player);
	return (0);
}

static void	setup_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, 17, 0, close_window, data);
	mlx_hook(data->mlx.win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx.ptr, moves, data);
}

int	main(int argc, char **argv)
{
	t_data		data;
	const char	*map_path;

	if (argc >= 2)
		map_path = argv[1];
	else
		map_path = "maps/simple_test.cub";
	if (init_game(&data, (char *)map_path) != 0)
		return (1);
	setup_hooks(&data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
