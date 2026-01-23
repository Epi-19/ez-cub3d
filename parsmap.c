#include "cub3d.h"

int is_valid_map_char(char c)
{
	return (c == '0' || c == '1'
		|| c == 'N' || c == 'S'
		|| c == 'E' || c == 'W'
		|| c == ' ');
}

char **get_map(char **file, int start)
{
	int i;
	int j;
	char **map;

	i = start;
	while (file[i])
		i++;

	map = malloc(sizeof(char *) * (i - start + 1));
	if (!map)
		return (NULL);

	j = 0;
	while (file[start])
		map[j++] = ft_strdup(file[start++]);
	map[j] = NULL;

	return (map);
}

int map_max_width(char **map)
{
	int i;
	int max;

	max = 0;
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

void normalize_map(char **map)
{
	int i;
	int len;
	int max;
	char *new;

	max = map_max_width(map);
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < max)
		{
			new = malloc(max + 1);
			ft_memset(new, ' ', max);
			ft_memcpy(new, map[i], len);
			new[max] = '\0';
			free(map[i]);
			map[i] = new;
		}
		i++;
	}
}

char **dup_map(char **map)
{
	int i;
	char **copy;

	i = 0;
	while (map[i])
		i++;

	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);

	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void flood_fill(char **map, int x, int y)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
		error("Map ouverte");

	if (map[y][x] == ' ' )
		error("Map ouverte");

	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;

	map[y][x] = 'F';

	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void check_map_closed(char **map, t_data *data)
{
	char **copy;

	copy = dup_map(map);
	flood_fill(copy, data->player_x, data->player_y);
	free_map(copy);
}

void find_player(char **map, t_data *data)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				data->player_x = j;
				data->player_y = i;
				data->player_dir = map[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		error("La map doit contenir exactement un joueur");
}


