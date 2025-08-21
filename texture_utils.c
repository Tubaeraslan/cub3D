/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teraslan <teraslan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:24:14 by teraslan          #+#    #+#             */
/*   Updated: 2025/08/21 14:15:30 by teraslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture *choose_texture(t_data *data)
{
	t_player *p = data->player;
	if (p->side == 0) // X ekseninde çarpma (dikey duvar)
		return (p->rayDirX > 0) ? &data->east : &data->west;
	else // Y ekseninde çarpma (yatay duvar)
		return (p->rayDirY > 0) ? &data->south : &data->north;
}
