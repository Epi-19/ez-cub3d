#include "cub3d.h"

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
#include <stdio.h>
#include "cub3d.h" // ton header avec t_data, prototypes ft_parsing, init_data, etc.

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
    {
        printf("Usage: %s <map.cub>\n", argv[0]);
        return 1;
    }

    // Initialisation des flags / couleurs / textures
    ft_init_data(&data);

    // Parsing du fichier
    if (ft_parsing(argv[1], &data))
        return 1; // erreur déjà affichée par error()

    // Affichage pour test
    printf("=== Parsing réussi ===\n");

    printf("Couleur sol : 0x%06X\n", data.floor_color);
    printf("Couleur plafond : 0x%06X\n", data.ceiling_color);

    printf("Textures :\n");
    printf("NO: %s\n", data.no ? data.no : "NULL");
    printf("SO: %s\n", data.so ? data.so : "NULL");
    printf("WE: %s\n", data.we ? data.we : "NULL");
    printf("EA: %s\n", data.ea ? data.ea : "NULL");

    printf("Début de la map : ligne %d\n", data.map_start);

    // Free des textures
    free(data.no);
    free(data.so);
    free(data.we);
    free(data.ea);

    return 0;
}
