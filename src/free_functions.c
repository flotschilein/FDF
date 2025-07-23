/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:30:53 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/23 16:59:59 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_points_render(t_map *map)
{
	int	y;

	if (!map->points_render)
		return ;
	y = 0;
	while (y < map->height)
	{
		free(map->points_render[y]);
		y++;
	}
	free(map->points_render);
	map->points_render = NULL;
}

void	free_points_in(t_map *map)
{
	int	y;

	if (!map->points_in)
		return ;
	y = 0;
	while (y < map->height)
	{
		free(map->points_in[y]);
		y++;
	}
	free(map->points_in);
	map->points_in = NULL;
}

void	cleanup_data(t_data *data)
{
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (data->map)
	{
		free_points_in(data->map);
		free_points_render(data->map);
		free(data->map);
	}
}
