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
int check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		return (1);
	}
	return (0);
}
int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != 0)
		return (1);
	if(ft_parsing(argv[1], &data) != 0)
		return (1);
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