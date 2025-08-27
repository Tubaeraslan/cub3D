/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:47:43 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/27 14:17:57 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*setup_texture(t_data *data, t_draw draw, t_tex_calc *calc)
{
	t_texture	*tex;
	double		wall_x;
	int			line_height;

	tex = choose_texture(data);
	if (!tex || !tex->img || !tex->addr)
		return (printf("ERROR\nTexture Error\n"),
			NULL);
	if (data->player->side == 0)
		wall_x = data->player->pos_y + draw.wall_dist * data->player->ray_dir_y;
	else
		wall_x = data->player->pos_x + draw.wall_dist * data->player->ray_dir_x;
	wall_x -= floor(wall_x);
	calc->tex_x = (int)(wall_x * (double)tex->width);
	if ((data->player->side == 0 && data->player->ray_dir_x > 0)
		|| (data->player->side == 1 && data->player->ray_dir_y < 0))
		calc->tex_x = tex->width - calc->tex_x - 1;
	line_height = (int)(SCREENHEIGHT / draw.wall_dist);
	calc->step = 1.0 * tex->height / line_height;
	calc->tex_pos = (draw.draw_start - SCREENHEIGHT / 2 + line_height / 2)
		* calc->step;
	return (tex);
}

void	draw_wall_line(t_data *data, int *img_data, int line, t_draw draw)
{
	t_texture	*tex;
	int			*tex_data;
	t_tex_calc	calc;
	int			y;

	tex = setup_texture(data, draw, &calc);
	if (!tex)
		return ;
	tex_data = tex->addr;
	y = draw.draw_start;
	while (y < draw.draw_end)
	{
		img_data[y * (line / 4)
			+ draw.x] = tex_data[((int)calc.tex_pos & (tex->height - 1))
			* tex->width + calc.tex_x];
		calc.tex_pos += calc.step;
		y++;
	}
}

double	find_wall_distance(t_player *player)
{
	if (player->side == 0)
		return ((player->map_x - player->pos_x + (1 - player->step_x) / 2.0)
			/ player->ray_dir_x);
	else
		return ((player->map_y - player->pos_y + (1 - player->step_y) / 2.0)
			/ player->ray_dir_y);
}

void	dda_algorithm(t_data *data)
{
	data->player->hit = 0;
	while (data->player->hit == 0)
	{
		if (data->player->side_dist_x < data->player->side_dist_y)
		{
			data->player->side_dist_x += data->player->delta_dist_x;
			data->player->map_x += data->player->step_x;
			data->player->side = 0;
		}
		else
		{
			data->player->side_dist_y += data->player->delta_dist_y;
			data->player->map_y += data->player->step_y;
			data->player->side = 1;
		}
		if (data->player->map_y < 0 || data->player->map_y >= data->high
			|| data->player->map_x < 0 || data->player->map_x >= data->widht
			|| data->char_map[data->player->map_y][data->player->map_x] == '1')
			data->player->hit = 1;
	}
}
