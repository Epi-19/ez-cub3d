#include "cub3d.h"
void init_map(t_map *map)
{
    map->grid = NULL;
    map->width = 0;
    map->height = 0;
}
int	set_texture(char **dest, char *path, const char *id)
{
	if (*dest)
		return (error_msg("Duplicate texture identifier"));
	*dest = trim_path(path);
	if (!*dest)
		return (error_msg("Memory allocation failed"));
	return (0);
}
int	set_color(int *color, char *line, char type)
{
	int	r;
	int	g;
	int	b;

	if (*color != -1)
		return (error_msg("Duplicate color identifier"));

	char *color_str = line + 2;
	while (*color_str == ' ')
		color_str++;
	if (parse_rgb(color_str, &r, &g, &b) == -1)
		return (error_msg("Invalid RGB color"));
	*color = (r << 16) | (g << 8) | b;
	return (0);
}
int	parse_identifier(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_texture(&data->north_path, line + 3, "NO"));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_texture(&data->south_path, line + 3, "SO"));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_texture(&data->west_path, line + 3, "WE"));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_texture(&data->east_path, line + 3, "EA"));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (set_color(&data->floor_color, line, 'F'));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (set_color(&data->ceiling_color, line, 'C'));
	return (-1); // non reconnu → probablement une ligne de map
}

int	parse_file(int fd, t_data *data)
{
	char	*line;
	int		map_started = 0;

	while ((line = get_next_line_simple(fd)))
	{
		if (!map_started && line[0] == '\0')
			free(line);
		else if (!map_started && parse_identifier(line, data) == 0)
			free(line);
		else
		{
			map_started = 1;
			if (parse_map_line(line, data) == -1)
				return (free(line), -1);
		}
	}
	if (data->map.height == 0)
		return (error_msg("Missing map data"));
	return (0);
}

int	load_map(const char *filename, t_data *data)
{
	int		fd;
	char	*line;

    fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg("Cannot open map file"));
    init_map(&data->map);
}