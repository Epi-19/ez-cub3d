#include "cub3d.h"

void	destroy_mlx(t_mlx *mlx)
{
	if (mlx->img.ptr)
		mlx_destroy_image(mlx->ptr, mlx->img.ptr);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
	}
}

int	init_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (printf("Error: mlx_init() failed\n"), 1);

	mlx->win = mlx_new_window(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!mlx->win)
		return (printf("Error: mlx_new_window() failed\n"), destroy_mlx(mlx), 1);

	mlx->img.ptr = mlx_new_image(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx->img.ptr)
		return (printf("Error: mlx_new_image() failed\n"), destroy_mlx(mlx), 1);

	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr,
			&mlx->img.bpp, &mlx->img.line_len, &mlx->img.endian);
	if (!mlx->img.addr)
		return (printf("Error: mlx_get_data_addr() failed\n"), destroy_mlx(mlx), 1);

	return (0);
}