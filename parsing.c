#include "cub3d.h"

void	check_config_complete(t_data *data)
{
	if (!data->has_floor || !data->has_ceiling
		|| !data->has_no || !data->has_so
		|| !data->has_we || !data->has_ea)
		error("Configuration incomplète : couleurs ou textures manquantes", data, NULL);
}

int	is_line_empty(char *line)
{
	int	i = 0;

	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	before_map(char **file, t_data *data)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (is_line_empty(file[i]))
		{
			i++;
			continue;
		}
		else if (file[i][0] == 'F' && file[i][1] == ' ')
			parse_color(file[i] + 2, data, 'F');
		else if (file[i][0] == 'C' && file[i][1] == ' ')
			parse_color(file[i] + 2, data, 'C');
		else if (!ft_strncmp(file[i], "NO ", 3))
			parse_texture(file[i] + 3, &data->no, &data->has_no, data);
		else if (!ft_strncmp(file[i], "SO ", 3))
			parse_texture(file[i] + 3, &data->so, &data->has_so, data);
		else if (!ft_strncmp(file[i], "WE ", 3))
			parse_texture(file[i] + 3, &data->we, &data->has_we, data);
		else if (!ft_strncmp(file[i], "EA ", 3))
			parse_texture(file[i] + 3, &data->ea, &data->has_ea, data);
		else
			break; // 👉 ici seulement : début de la map
		i++;
	}
	return (i);
}

void ft_init_data(t_data *data)
{
	data->floor_color = 0;
	data->ceiling_color = 0;
	data->has_floor = 0;
	data->has_ceiling = 0;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->has_no = 0;
	data->has_so = 0;
	data->has_we = 0;
	data->has_ea = 0;
	data->map_start = 0;
}
int ft_parsing(char *path, t_data *data)
{
	char **file;

	file = read_file(path);
	if (!file)
		return (ft_putstr_fd("Error\nFailed to read file\n", 2), 1);
	data->map_start = before_map(file, data);
	free_tab(file);
	return (0);
}