/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:24:37 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/21 15:14:27 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_program(t_data *data)
{
	(void)data;
    //free
    exit(0);
    return (0);
}

int	key_hook(int keycode, t_data *data)
{
	// Linux: W=119, S=115, A=97, D=100, ESC=65307
	double moveSpeed = 0.1;
	if (keycode == 65307) // ESC
		exit(0);
	if (keycode == 119) // W
	{
		double newX = data->player->posX + data->player->dirX * moveSpeed;
		double newY = data->player->posY + data->player->dirY * moveSpeed;
		if (newX >= 0 && newX < data->widht && newY >= 0 && newY < data->high && data->char_map[(int)newY][(int)newX] != '1')
		{
			data->player->posX = newX;
			data->player->posY = newY;
		}
	}
	if (keycode == 115) // S
	{
		double newX = data->player->posX - data->player->dirX * moveSpeed;
		double newY = data->player->posY - data->player->dirY * moveSpeed;
		if (newX >= 0 && newX < data->widht && newY >= 0 && newY < data->high && data->char_map[(int)newY][(int)newX] != '1')
		{
			data->player->posX = newX;
			data->player->posY = newY;
		}
	}
	if (keycode == 97) // A (sola strafe)
	{
		double newX = data->player->posX - data->player->planeX * moveSpeed;
		double newY = data->player->posY - data->player->planeY * moveSpeed;
		if (newX >= 0 && newX < data->widht && newY >= 0 && newY < data->high && data->char_map[(int)newY][(int)newX] != '1')
		{
			data->player->posX = newX;
			data->player->posY = newY;
		}
	}
	if (keycode == 100) // D (sağa strafe)
	{
		double newX = data->player->posX + data->player->planeX * moveSpeed;
		double newY = data->player->posY + data->player->planeY * moveSpeed;
		if (newX >= 0 && newX < data->widht && newY >= 0 && newY < data->high && data->char_map[(int)newY][(int)newX] != '1')
		{
			data->player->posX = newX;
			data->player->posY = newY;
		}
	}
	double rotSpeed = 0.08;
	if (keycode == 65363) // Sağ ok tuşu (right arrow)
	{
		double oldDirX = data->player->dirX;
		data->player->dirX = data->player->dirX * cos(rotSpeed) - data->player->dirY * sin(rotSpeed);
		data->player->dirY = oldDirX * sin(rotSpeed) + data->player->dirY * cos(rotSpeed);
		double oldPlaneX = data->player->planeX;
		data->player->planeX = data->player->planeX * cos(rotSpeed) - data->player->planeY * sin(rotSpeed);
		data->player->planeY = oldPlaneX * sin(rotSpeed) + data->player->planeY * cos(rotSpeed);
	}
	if (keycode == 65361) // Sol ok tuşu (left arrow)
	{
		double oldDirX = data->player->dirX;
		data->player->dirX = data->player->dirX * cos(-rotSpeed) - data->player->dirY * sin(-rotSpeed);
		data->player->dirY = oldDirX * sin(-rotSpeed) + data->player->dirY * cos(-rotSpeed);
		double oldPlaneX = data->player->planeX;
		data->player->planeX = data->player->planeX * cos(-rotSpeed) - data->player->planeY * sin(-rotSpeed);
		data->player->planeY = oldPlaneX * sin(-rotSpeed) + data->player->planeY * cos(-rotSpeed);
	}
	draw_image(data); // Ekranı güncelle
	return (0);
}