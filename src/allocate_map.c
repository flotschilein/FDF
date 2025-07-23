/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:40:02 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/23 16:43:04 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

bool	allocate_map_render(t_map *map, int width, int height)
{
	int	y;

	map->points_render = malloc(sizeof(t_point_render *) * height);
	if (!map->points_render)
		return (false);
	y = 0;
	while (y < height)
	{
		map->points_render[y] = malloc(sizeof(t_point_render) * width);
		if (!map->points_render[y])
		{
			while (--y >= 0)
				free(map->points_render[y]);
			free(map->points_render);
			return (false);
		}
		y++;
	}
	return (true);
}

bool	allocate_map_in(t_map *map, int width, int height)
{
	int	y;

	map->points_in = malloc(sizeof(t_point_in *) * height);
	if (!map->points_in)
		return (false);
	y = 0;
	while (y < height)
	{
		map->points_in[y] = malloc(sizeof(t_point_in) * width);
		if (!map->points_in[y])
		{
			while (--y >= 0)
				free(map->points_in[y]);
			free(map->points_in);
			return (false);
		}
		y++;
	}
	return (true);
}
