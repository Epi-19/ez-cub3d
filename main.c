#include "cub3d.h"

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	destroy_mlx(&data->mlx);
	exit(0);
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == ESC_KEY)
	{
		destroy_mlx(&data->mlx);
		exit(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	data.floor_color = -1;
	data.ceiling_color = -1;
	if (init_mlx(&data.mlx) != 0)
		return (1);
	mlx_hook(data.mlx.win, 17, 0, close_window, &data);
	mlx_key_hook(data.mlx.win, key_press, &data);
	mlx_loop(data.mlx.ptr);
	return (0);
}