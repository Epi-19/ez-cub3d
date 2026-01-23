#include "cub3d.h"

int	has_xpm_extension(char *path)
{
	int	len;

//    printf("dd : %s\n", path);
	len = ft_strlen(path);
//    printf("len : %d\n", len);
	if (len < 4)
		return (0);
    //printf("%s\n", path + len - 4);
    int res = !ft_strncmp(path + len - 4, ".xpm", 4);
   // printf("res : %d\n", res);
	return (res);
}

void	parse_texture(char *line, char **dest, int *flag, t_data *data)
{
	int		fd;
	char	*path;

	if (*flag)
		error("Texture en double", data, NULL);

	/* trim espaces + tab + newline */
	path = ft_strtrim(line, " \t\n");
	if (!path || path[0] == '\0')
		error("Chemin de texture invalide", data, NULL);

	if (!has_xpm_extension(path))
		error("Texture non .xpm", data, NULL);

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error("Texture introuvable ou non lisible", data, NULL);
	close(fd);

	*dest = path;
	*flag = 1;
}
