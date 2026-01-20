#include "cub3d.h"

void	parse_color(char *str, t_data *data, char type)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		error("Invalid color format");

	if (!is_number(rgb[0]) || !is_number(rgb[1]) || !is_number(rgb[2]))
		error("Color is not numeric");

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error("Color out of range");
	if (type == 'F')
	
}
int before_map(char **file, t_data *data)
{
	int i;

	i = 0;
	while(file[i])
	{
		if (file[i][0] == 'F' && file[i][1] == ' ')
			parse_color(file + 2, data, 'F');
		else if (file[i][0] == 'C' && file[i][1] == ' ')
			parse_color(file + 2, data, 'C');
		i++;
	}
}
int ft_parsing(char *path, t_data *data)
{
	char **file;

	file = read_file(path);
	if (!file)
		return (ft_putstr_fd("Error\nFailed to read file\n", 2), 1);

	before_map(file, data);
	free(file);
	return (0);
}