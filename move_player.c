/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:14:05 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/25 12:55:41 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_vector(t_player *p, double *mvx, double *mvy)
{
	*mvx = 0.0;
	*mvy = 0.0;
	if (p->move_forward)
	{
		*mvx += p->dir_x;
		*mvy += p->dir_y;
	}
	if (p->move_backward)
	{
		*mvx -= p->dir_x;
		*mvy -= p->dir_y;
	}
	if (p->move_right)
	{
		*mvx += p->plane_x;
		*mvy += p->plane_y;
	}
	if (p->move_left)
	{
		*mvx -= p->plane_x;
		*mvy -= p->plane_y;
	}
}

static t_move	calculate_move(t_player *p)
{
	double	mvx;
	double	mvy;
	double	len;
	t_move	move;

	calculate_vector(p, &mvx, &mvy);
	len = sqrt(mvx * mvx + mvy * mvy);
	if (len > 0.0)
	{
		mvx = mvx / len * p->move_speed;
		mvy = mvy / len * p->move_speed;
		move.new_x = p->pos_x + mvx;
		move.new_y = p->pos_y + mvy;
	}
	else
	{
		move.new_x = p->pos_x;
		move.new_y = p->pos_y;
	}
	return (move);
}

static void	try_move(t_data *data, t_player *p, t_move move)
{
	int	can_move_x;
	int	can_move_y;

	can_move_x = ((int)p->pos_y >= 0 && (int)p->pos_y < data->high
			&& (int)move.new_x >= 0 && (int)move.new_x < data->widht
			&& data->char_map[(int)p->pos_y][(int)move.new_x] != '1');
	can_move_y = ((int)move.new_y >= 0 && (int)move.new_y < data->high
			&& (int)p->pos_x >= 0 && (int)p->pos_x < data->widht
			&& data->char_map[(int)move.new_y][(int)p->pos_x] != '1');
	if (can_move_x && can_move_y)
	{
		p->pos_x = move.new_x;
		p->pos_y = move.new_y;
	}
}

void	move_player(t_data *data)
{
	t_player	*p;
	t_move		move;

	p = data->player;
	move = calculate_move(p);
	try_move(data, p, move);
}

void	rotate_player(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}
