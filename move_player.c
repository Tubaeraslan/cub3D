/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:14:05 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/23 18:44:46 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data)
{
	t_player	*p;
	double		mvx;
	double		mvy;
	double		len;
	double		newX;
	double		newY;
	int			can_move_x;
	int			can_move_y;

	p = data->player;
	mvx = 0.0;
	mvy = 0.0;
	if (p->move_forward)
		mvx += p->dir_x, mvy += p->dir_y;
	if (p->move_backward)
		mvx -= p->dir_x, mvy -= p->dir_y;
	if (p->move_right)
		mvx += p->plane_x, mvy += p->plane_y;
	if (p->move_left)
		mvx -= p->plane_x, mvy -= p->plane_y;
	len = sqrt(mvx * mvx + mvy * mvy);
	if (len > 0.0)
	{
		mvx = mvx / len * p->move_speed;
		mvy = mvy / len * p->move_speed;
		newX = p->pos_x + mvx;
		newY = p->pos_y + mvy;
		can_move_x = ((int)p->pos_y >= 0 && (int)p->pos_y < data->high &&
			(int)newX >= 0 && (int)newX < data->widht &&
			data->char_map[(int)p->pos_y][(int)newX] != '1');
		can_move_y = ((int)newY >= 0 && (int)newY < data->high &&
			(int)p->pos_x >= 0 && (int)p->pos_x < data->widht &&
			data->char_map[(int)newY][(int)p->pos_x] != '1');
		if (can_move_x && can_move_y)
			p->pos_x = newX, p->pos_y = newY;
	}
}

void	rotate_player(t_player *p, double angle)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = oldDirX * sin(angle) + p->dir_y * cos(angle);
	oldPlaneX = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = oldPlaneX * sin(angle) + p->plane_y * cos(angle);
}
