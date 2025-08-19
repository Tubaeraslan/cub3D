/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapctl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:43:31 by skaynar           #+#    #+#             */
/*   Updated: 2025/08/19 10:45:18 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int check_map(char **av, t_data *data)
{
    if(!check_map_name(av[1]))
        return(printf("Invalid map name\n"),0);
    if(!is_true_map(av[1], data))
    	{
			return(0);
		}
		
	if(data->feature->we)
		printf("%s",data->feature->we);
	if(data->feature->so)
		printf("%s",data->feature->so);
	if(data->feature->no)
		printf("%s",data->feature->no);			
	if(data->feature->ea)
		printf("%s",data->feature->ea);
	if(data->feature->f)
		printf("%s",data->feature->f);
	if(data->feature->c)
		printf("%s",data->feature->c);
    // while (data->map)
    // { 
	// 	if(data->map != NULL)
    //     {
	// 		printf("%s", data->map->map_line);
	// 		data->map = data->map->next;
	// 	}
	// 	else
	// 		printf("NOMAP\n");
	// }
    return(1);
}