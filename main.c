#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
    if (init_mlx(&data.mlx) != 0)
		return (1);
    if (load_map(argv[1], &data) == -1)
		return (printf("Error: failed to load map\n"), 1);
    
	
}