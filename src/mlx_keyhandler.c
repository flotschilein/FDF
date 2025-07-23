/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyhandler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:02:25 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/23 18:03:19 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	else if (keydata.key == MLX_KEY_UP)
		data->camera.offset_y -= 10;
	else if (keydata.key == MLX_KEY_DOWN)
		data->camera.offset_y += 10;
	else if (keydata.key == MLX_KEY_LEFT)
		data->camera.offset_x -= 10;
	else if (keydata.key == MLX_KEY_RIGHT)
		data->camera.offset_x += 10;
	else if (keydata.key == MLX_KEY_EQUAL && data->camera.zoom < 50)
		data->camera.zoom *= 1.1;
	else if (keydata.key == MLX_KEY_MINUS && data->camera.zoom > 0.1)
		data->camera.zoom *= 0.9;
	free_points_render(data->map);
	calc_render_points(data->map, &data->camera);
	mlx_delete_image(data->mlx, data->img);
	init_image(&data->img, data->mlx);
	render_map(data);
}
