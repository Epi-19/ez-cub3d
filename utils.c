#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i = 0;

	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

void error(char *msg, t_data *data, char **file)
{
    printf("Error\n%s\n", msg);

    if (file)
        free_tab(file);

    if (data)
    {
        free(data->no);
        free(data->so);
        free(data->we);
        free(data->ea);
        // mlx ou map simalloc
    }

    exit(1);
}
