/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodebacq <rodebacq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 02:23:39 by rodebacq          #+#    #+#             */
/*   Updated: 2026/01/22 14:36:26 by rodebacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <limits.h>

# define WINDOW_WIDTH       1200
# define WINDOW_HEIGHT      800

# define ESC_KEY            65307
# define KEY_W              119
# define KEY_A              97
# define KEY_S              115
# define KEY_D              100
# define KEY_LEFT           65363
# define KEY_RIGHT          65361

# define MOVE_SPEED         0.03
# define ROT_SPEED          0.03


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# if BUFFER_SIZE > 2147483646
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_read_to_left_str(int fd, char *str);
char	*get_next_line(int fd);
char	*ft_cut_str(char *str);
char	*ft_get_line(char *str);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_map
{
    char	**grid;
    int		width;
    int		height;
}	t_map;
typedef struct s_img
{
	void	*ptr;
	char	*addr;
    int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
    t_img	img;
}   t_mlx;

typedef struct s_data
{
	int		floor_color;
	int		ceiling_color;
	int		has_floor;
	int 	has_ceiling;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		has_no;
	int		has_so;
	int		has_we;
	int		has_ea;
	int 	map_start;

}	t_data;

// mlx_utils.c
int     init_mlx(t_mlx *mlx);
void	destroy_mlx(t_mlx *mlx);

//parsing.c
void ft_init_data(t_data *data);

// uptodown.c
void    parse_color(char *str, t_data *data, char type);
int     ft_parsing(char *path, t_data *data);
void    check_config_complete(t_data *data);
//utils.c
void    free_tab(char **tab);
void    error(char *msg, t_data *data, char **file);
//neso.c
void    parse_texture(char *line, char **dest, int *flag, t_data *data);
int     has_xpm_extension(char *path);

char	**read_file(char *path);

#endif