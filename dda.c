/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:47:43 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/22 18:11:33 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*setup_texture(t_data *data, t_draw draw, t_tex_calc *calc)
{
	t_texture	*tex;
	double		wall_x;

	tex = choose_texture(data);
	if (!tex || !tex->img || !tex->addr)
		return (printf("[ERROR] draw_wall_line: Seçilen texture NULL!\n"), NULL);
	if (data->player->side == 0)
		wall_x = data->player->posY + draw.wall_dist * data->player->rayDirY;
	else
		wall_x = data->player->posX + draw.wall_dist * data->player->rayDirX;
	wall_x -= floor(wall_x);
	calc->texX = (int)(wall_x * (double)tex->width);
	if ((data->player->side == 0 && data->player->rayDirX > 0)
		|| (data->player->side == 1 && data->player->rayDirY < 0))
		calc->texX = tex->width - calc->texX - 1;
	calc->step = 1.0 * tex->height / (draw.drawEnd - draw.drawStart);
	calc->texPos = (draw.drawStart - screenHeight / 2
			+ (draw.drawEnd - draw.drawStart) / 2) * calc->step;
	return (tex);
}

void	draw_wall_line(t_data *data, int *img_data, int size_line, t_draw draw)
{
	t_texture	*tex;
	int			*tex_data;
	t_tex_calc	calc;
	int			y;

	tex = setup_texture(data, draw, &calc);
	if (!tex)
		return ;
	tex_data = tex->addr;
	y = draw.drawStart;
	while (y < draw.drawEnd)
	{
		img_data[y * (size_line / 4) + draw.x] = tex_data[((int)calc.texPos
				& (tex->height - 1)) * (tex->size_line / 4) + calc.texX];
		calc.texPos += calc.step;
		y++;
	}
}

double	find_wall_distance(t_player *player)
{
	double	perp_wall_dist;

	if (player->side == 0)
		perp_wall_dist = fabs((player->mapX - player->posX
					+ (1 - player->stepX) / 2.0) / player->rayDirX);
	else
		perp_wall_dist = fabs((player->mapY - player->posY
					+ (1 - player->stepY) / 2.0) / player->rayDirY);
	return (perp_wall_dist);
}

void	dda_algorithm(t_data *data)
{
	int	limit;

	data->player->hit = 0;
	limit = 0;
	while (data->player->hit == 0 && limit++ < 1000)
	{
		if (data->player->sideDistX < data->player->sideDistY)
		{
			data->player->sideDistX += data->player->deltaDistX;
			data->player->mapX += data->player->stepX;
			data->player->side = 0;
		}
		else
		{
			data->player->sideDistY += data->player->deltaDistY;
			data->player->mapY += data->player->stepY;
			data->player->side = 1;
		}
		if (data->player->mapY < 0 || data->player->mapY >= data->high
			|| data->player->mapX < 0 || data->player->mapX >= data->widht
			||data->char_map[data->player->mapY][data->player->mapX] == '1')
			data->player->hit = 1;
	}
}
