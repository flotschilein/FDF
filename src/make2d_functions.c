/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make2d_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:56:13 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/23 17:56:39 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	project_to_2d(t_map *map, int x, int y, t_camerainfo *cam)
{
	double	angle;
	double	iso_x;
	double	iso_y;
	double	scaled_x;
	double	scaled_y;

	angle = M_PI / 6;
	iso_x = (x - y) * cos(angle);
	iso_y = (x + y) * sin(angle) - map->points_in[y][x].z;
	scaled_x = iso_x * cam->zoom + cam->offset_x;
	scaled_y = iso_y * cam->zoom + cam->offset_y;
	map->points_render[y][x].x = round(scaled_x);
	map->points_render[y][x].y = round(scaled_y);
}

bool	calc_render_points(t_map *map, t_camerainfo *cam)
{
	int	y;
	int	x;

	if (!allocate_map_render(map, map->width, map->height))
		return (false);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			project_to_2d(map, x, y, cam);
			x++;
		}
		y++;
	}
	return (true);
}
