/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:47:16 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/24 14:32:15 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static bool	init_map(t_map *map, char *filename, t_camerainfo *cam)
{
	if (!calc_map_size(&map->width, &map->height, filename))
		return (false);
	if (!read_map_points(map, filename))
		return (false);
	if (!calc_render_points(map, cam))
	{
		free_points_in(map);
		free_points_render(map);
		return (false);
	}
	return (true);
}

static bool	init_mlx(t_data *data)
{
	data->mlx = mlx_init(1000, 1000, "FDF", false);
	if (!data->mlx)
		return (false);
	return (true);
}

static void	init_camera(t_camerainfo *camera)
{
	camera->zoom = 1;
	camera->offset_x = 500;
	camera->offset_y = 500;
}

bool	init_image(mlx_image_t **img, mlx_t *mlx)
{
	*img = mlx_new_image(mlx, 1000, 1000);
	if (!*img)
		return (false);
	mlx_image_to_window(mlx, *img, 0, 0);
	return (true);
}

bool	init_all(t_data *data, char *filename)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (ft_putstr_fd("Memory allocation failed\n", 2), false);
	init_camera(&data->camera);
	if (!init_mlx(data))
		return (free(data->map), false);
	if (!init_map(data->map, filename, &data->camera))
		return (free(data->map), mlx_terminate(data->mlx),
			ft_putstr_fd("Error initializing map\n", 2), false);
	if (!init_image(&data->img, data->mlx))
		return (false);
	render_map(data);
	return (true);
}
