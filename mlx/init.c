
#include "../cub3d.h"

static int	init_window(t_mlx *mlx)
{
	mlx->win = mlx_new_window(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!mlx->win)
	{
		printf("Error: mlx_new_window() failed\n");
		return (0);
	}
	return (1);
}

static int	init_image(t_mlx *mlx)
{
	mlx->img.ptr = mlx_new_image(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx->img.ptr)
	{
		printf("Error: mlx_new_image() failed\n");
		return (0);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp,
			&mlx->img.line_len, &mlx->img.endian);
	if (!mlx->img.addr)
	{
		printf("Error: mlx_get_data_addr() failed\n");
		return (0);
	}
	return (1);
}

int	init_mlx(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
	{
		printf("Error: mlx_init() failed\n");
		return (1);
	}
	if (!init_window(mlx))
	{
		destroy_mlx(mlx);
		return (1);
	}
	if (!init_image(mlx))
	{
		destroy_mlx(mlx);
		return (1);
	}
	return (0);
}

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
