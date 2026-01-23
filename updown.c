#include "cub3d.h"

#include <ctype.h>

int is_number(const char *str)
{
    int i = 0;

    if (!str || str[0] == '\0')
        return 0; // chaîne vide ou NULL -> pas un nombre

    // gérer un signe + ou - au début
    if (str[0] == '+' || str[0] == '-')
        i++;

    if (str[i] == '\0')
        return 0; // juste un + ou - -> pas un nombre

    // vérifier que tous les caractères restants sont des chiffres
    while (str[i])
    {
        if (!isdigit((unsigned char)str[i]))
            return 0;
        i++;
    }
    return 1; // tout est ok, c'est un nombre
}

t_rgb	get_rgb(char *str, t_data *data)
{
	t_rgb	rgb_val;
	char	**rgb;
	char	*tmp;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		error("Format couleur invalide",data, NULL);
	tmp = ft_strtrim(rgb[0], " \t\n");
	if (!is_number(tmp))
		error("Couleur non numérique", data, NULL);
	rgb_val.r = ft_atoi(tmp);
	free(tmp);
	tmp = ft_strtrim(rgb[1], " \t\n");
	if (!is_number(tmp))
		error("Couleur non numérique", data, NULL);
	rgb_val.g = ft_atoi(tmp);
	free(tmp);
	tmp = ft_strtrim(rgb[2], " \t\n");
	if (!is_number(tmp))
		error("Couleur non numérique", data, NULL);
	rgb_val.b = ft_atoi(tmp);
	free(tmp);
	free_tab(rgb);
	return (rgb_val);
}

int	parse_rgb(char *str, t_data *data)
{
	t_rgb	c;

	c = get_rgb(str, data);
	if (c.r < 0 || c.r > 255
		|| c.g < 0 || c.g > 255
		|| c.b < 0 || c.b > 255)
		error("Couleur hors limites", data, NULL);
	return ((c.r << 16) | (c.g << 8) | c.b);
}

void	parse_color(char *str, t_data *data, char type)
{
	int	color;
   //printf("Parsing color %c: %s\n", type, str);
	color = parse_rgb(str, data);
	if (type == 'F')
	{
		if (data->has_floor)
			error("Couleur sol en double", data, NULL);
		data->floor_color = color;
		data->has_floor = 1;
	}
	else if (type == 'C')
	{
		if (data->has_ceiling)
			error("Couleur plafond en double", data, NULL);
		data->ceiling_color = color;
		data->has_ceiling = 1;
	}
}
