/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 02:23:39 by rodebacq          #+#    #+#             */
/*   Updated: 2026/01/20 10:35:39 by rodantec         ###   ########.fr       */
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

int	load_map(const char *filename, t_data *data);


#endif