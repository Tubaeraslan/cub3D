/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:24:14 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/19 14:24:40 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void *choose_texture(t_data *data)
{
	t_player *p = data->player;

	if (p->side == 0) { // X ekseninde çarpma (dikey duvar)
		if (p->rayDirX > 0)
			return data->tex_east;
		else
			return data->tex_west;
	} else {            // Y ekseninde çarpma (yatay duvar)
		if (p->rayDirY > 0)
			return data->tex_south;
		else
			return data->tex_north;
	}
}
