/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:28:15 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/23 17:47:20 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int exit_program(t_data *data)
{
    // temizleme ekleyin gerekiyorsa
    (void)data;
    exit(0);
    return (0);
}

/* key press: set flag */
int key_press(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
        return (exit_program(data), 0);
    if (keycode == KEY_W) data->player->move_forward = 1;
    if (keycode == KEY_S) data->player->move_backward = 1;
    if (keycode == KEY_A) data->player->move_left = 1;
    if (keycode == KEY_D) data->player->move_right = 1;
    if (keycode == KEY_LEFT) data->player->turn_left = 1;
    if (keycode == KEY_RIGHT) data->player->turn_right = 1;
    return (0);
}

/* key release: clear flag */
int key_release(int keycode, t_data *data)
{
    if (keycode == KEY_W) data->player->move_forward = 0;
    if (keycode == KEY_S) data->player->move_backward = 0;
    if (keycode == KEY_A) data->player->move_left = 0;
    if (keycode == KEY_D) data->player->move_right = 0;
    if (keycode == KEY_LEFT) data->player->turn_left = 0;
    if (keycode == KEY_RIGHT) data->player->turn_right = 0;
    return (0);
}

/* per-frame movement handler (normalize for diagonal & axis-separated collision) */
static void handle_movement(t_data *data)
{
    t_player *p = data->player;
    double mvx = 0.0, mvy = 0.0;
    double ms = p->moveSpeed;
    double rs = p->rotSpeed;
	int can_move_x = 0, can_move_y = 0;

    if (p->move_forward)  { mvx += p->dirX; mvy += p->dirY; }
    if (p->move_backward) { mvx -= p->dirX; mvy -= p->dirY; }
    if (p->move_right)    { mvx += p->planeX; mvy += p->planeY; }
    if (p->move_left)     { mvx -= p->planeX; mvy -= p->planeY; }

    /* normalize to avoid faster diagonal movement */
    double len = sqrt(mvx * mvx + mvy * mvy);
    if (len > 0.0)
    {
        mvx = mvx / len * ms;
        mvy = mvy / len * ms;
        double newX = p->posX + mvx;
        double newY = p->posY + mvy;
        /* axis-separated collision checks */
        if ((int)p->posY >= 0 && (int)p->posY < data->high &&
            (int)newX >= 0 && (int)newX < data->widht &&
            data->char_map[(int)p->posY][(int)newX] != '1')
            can_move_x = 1;
        if ((int)newY >= 0 && (int)newY < data->high &&
            (int)p->posX >= 0 && (int)p->posX < data->widht &&
            data->char_map[(int)newY][(int)p->posX] != '1')
            can_move_y = 1;
		if (can_move_x && can_move_y) {
            p->posX = newX;
            p->posY = newY;
        }
    }

    /* rotation */
    if (p->turn_left)
    {
        double oldDirX = p->dirX;
        p->dirX = p->dirX * cos(-rs) - p->dirY * sin(-rs);
        p->dirY = oldDirX * sin(-rs) + p->dirY * cos(-rs);
        double oldPlaneX = p->planeX;
        p->planeX = p->planeX * cos(-rs) - p->planeY * sin(-rs);
        p->planeY = oldPlaneX * sin(-rs) + p->planeY * cos(-rs);
    }
    if (p->turn_right)
    {
        double oldDirX = p->dirX;
        p->dirX = p->dirX * cos(rs) - p->dirY * sin(rs);
        p->dirY = oldDirX * sin(rs) + p->dirY * cos(rs);
        double oldPlaneX = p->planeX;
        p->planeX = p->planeX * cos(rs) - p->planeY * sin(rs);
        p->planeY = oldPlaneX * sin(rs) + p->planeY * cos(rs);
    }
}

int game_loop(void *param)
{
    t_data *data = (t_data *)param;
    handle_movement(data);
    draw_image(data); /* yeniden çiz */
    return (0);
}
