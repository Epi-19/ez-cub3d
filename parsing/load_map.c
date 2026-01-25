#include "../cub3d.h"

static char *dup_line_strip(const char *src)
{
	size_t len;
	char   *dst;

	len = strlen(src);
	while (len > 0 && (src[len - 1] == '\n' || src[len - 1] == '\r'))
		len--;
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	memcpy(dst, src, len);
	dst[len] = '\0';
	return (dst);
}

void init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->north_tex_path = NULL;
	map->south_tex_path = NULL;
	map->east_tex_path = NULL;
	map->west_tex_path = NULL;
}

static int parse_rgb_line(const char *s)
{
	int r, g, b;

	while (*s == ' ')
		s++;
	if (sscanf(s, "%d , %d , %d", &r, &g, &b) != 3)
		return (-1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int load_map(const char *filename, t_data *data)
{
	FILE	*fp;
	char	buffer[1024];
	char	**rows;
	int		cap;
	int		n;
	char	*line;
	int		w;
	int		map_started;

	init_map(&data->map);
	data->floor_color = -1;
	data->ceiling_color = -1;
	fp = fopen(filename, "r");
	if (!fp)
	{
		printf("Error: cannot open map file %s\n", filename);
		return (1);
	}
	cap = 16;
	rows = malloc(sizeof(char *) * cap);
	if (!rows)
	{
		fclose(fp);
		return (1);
	}
	n = 0;
	map_started = 0;
	while (fgets(buffer, sizeof(buffer), fp))
	{
		line = dup_line_strip(buffer);
		if (!line)
			break;
		if (!map_started)
		{
			if (ft_strncmp(line, "NO ", 3) == 0)
				data->map.north_tex_path = strdup(line + 3);
			else if (ft_strncmp(line, "SO ", 3) == 0)
				data->map.south_tex_path = strdup(line + 3);
			else if (ft_strncmp(line, "EA ", 3) == 0)
				data->map.east_tex_path = strdup(line + 3);
			else if (ft_strncmp(line, "WE ", 3) == 0)
				data->map.west_tex_path = strdup(line + 3);
			else if (ft_strncmp(line, "F ", 2) == 0)
				data->floor_color = parse_rgb_line(line + 2);
			else if (ft_strncmp(line, "C ", 2) == 0)
				data->ceiling_color = parse_rgb_line(line + 2);
			else if (line[0] == '\0')
			{
				free(line);
				continue;
			}
			else
				map_started = 1;
		}
		if (map_started)
		{
			w = (int)strlen(line);
			if (w > data->map.width)
				data->map.width = w;
			if (n == cap)
			{
				cap *= 2;
				char **tmp = realloc(rows, sizeof(char *) * cap);
				if (!tmp)
				{
					free(line);
					break;
				}
				rows = tmp;
			}
			rows[n++] = line;
		}
	}
	fclose(fp);
	data->map.height = n;
	if (n == 0)
	{
		free(rows);
		printf("Error: empty map file\n");
		return (1);
	}
	data->map.grid = malloc(sizeof(char *) * n);
	if (!data->map.grid)
	{
		for (int i = 0; i < n; i++)
			free(rows[i]);
		free(rows);
		return (1);
	}
	for (int i = 0; i < n; i++)
	{
		int len = (int)strlen(rows[i]);
		data->map.grid[i] = malloc(data->map.width + 1);
		if (!data->map.grid[i])
			return (1);
		for (int j = 0; j < data->map.width; j++)
		{
			char c = (j < len) ? rows[i][j] : '1';
			data->map.grid[i][j] = c;
		}
		data->map.grid[i][data->map.width] = '\0';
		free(rows[i]);
	}
	free(rows);
	/* Ensure borders are closed */
	for (int x = 0; x < data->map.width; x++)
	{
		data->map.grid[0][x] = '1';
		data->map.grid[data->map.height - 1][x] = '1';
	}
	for (int y = 0; y < data->map.height; y++)
	{
		data->map.grid[y][0] = '1';
		data->map.grid[y][data->map.width - 1] = '1';
	}
	return (0);
}