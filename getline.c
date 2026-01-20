#include "cub3d.h"

int	count_lines(char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

char	**read_file(char *path)
{
	int		fd;
	int		i;
	int		lines;
	char	**file;

	lines = count_lines(path);
	if (lines <= 0)
		return (NULL);
	file = malloc(sizeof(char *) * (lines + 1));
	if (!file)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	while (i < lines)
		file[i++] = get_next_line(fd);
	file[i] = NULL;
	close(fd);
	return (file);
}

