/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodebacq <rodebacq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 02:23:39 by rodebacq          #+#    #+#             */
/*   Updated: 2026/01/20 11:28:47 by rodebacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
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
size_t	ft_strlen(char *str);
char	*ft_strdup(char *s);


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
	t_mlx	mlx;
	t_map	map;
	int		floor_color;
	int		ceiling_color;
}	t_data;

// mlx_utils.c
int     init_mlx(t_mlx *mlx);
void	destroy_mlx(t_mlx *mlx);

//parsing.c

//getline.c

#endif