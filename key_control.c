/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:28:15 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/24 21:36:29 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_program(t_data *data)
{
	free_mlx(data);
	free_data(data, 0);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		return (exit_program(data), 0);
	if (keycode == KEY_W)
		data->player->move_forward = 1;
	if (keycode == KEY_S)
		data->player->move_backward = 1;
	if (keycode == KEY_A)
		data->player->move_left = 1;
	if (keycode == KEY_D)
		data->player->move_right = 1;
	if (keycode == KEY_LEFT)
		data->player->turn_left = 1;
	if (keycode == KEY_RIGHT)
		data->player->turn_right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->player->move_forward = 0;
	if (keycode == KEY_S)
		data->player->move_backward = 0;
	if (keycode == KEY_A)
		data->player->move_left = 0;
	if (keycode == KEY_D)
		data->player->move_right = 0;
	if (keycode == KEY_LEFT)
		data->player->turn_left = 0;
	if (keycode == KEY_RIGHT)
		data->player->turn_right = 0;
	return (0);
}

static void	handle_movement(t_data *data)
{
	t_player	*p;

	p = data->player;
	move_player(data);
	if (p->turn_left)
		rotate_player(p, -p->rot_speed);
	if (p->turn_right)
		rotate_player(p, p->rot_speed);
}

int	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	handle_movement(data);
	draw_image(data);
	return (0);
}
