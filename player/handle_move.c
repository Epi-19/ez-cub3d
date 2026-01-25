#include "../cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->key_w = 1;
	if (keycode == KEY_A)
		data->key_a = 1;
	if (keycode == KEY_S)
		data->key_s = 1;
	if (keycode == KEY_D)
		data->key_d = 1;
	if (keycode == KEY_RIGHT)
		data->key_right = 1;
	if (keycode == KEY_LEFT)
		data->key_left = 1;
	if (keycode == ESC_KEY)
		exit(0);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->key_w = 0;
	if (keycode == KEY_A)
		data->key_a = 0;
	if (keycode == KEY_S)
		data->key_s = 0;
	if (keycode == KEY_D)
		data->key_d = 0;
	if (keycode == KEY_RIGHT)
		data->key_right = 0;
	if (keycode == KEY_LEFT)
		data->key_left = 0;
	return (0);
}

int	moves(t_data *data)
{
	if (data->key_w)
		move_w(&data->player, &data->map);
	if (data->key_a)
		move_a(&data->player, &data->map);
	if (data->key_s)
		move_s(&data->player, &data->map);
	if (data->key_d)
		move_d(&data->player, &data->map);
	if (data->key_left)
		rotate_left(&data->player);
	if (data->key_right)
		rotate_right(&data->player);
	cast_rays(data, &data->player);
	return (0);
}
