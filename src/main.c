/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:41 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/23 17:02:58 by fbraune          ###   ########.fr       */
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

void	draw_line_low(t_data *data, t_point_render a, t_point_render b)
{
	int	dx;
	int	dy;
	int	err;
	int	y;

	dx = b.x - a.x;
	dy = b.y - a.y;
	y = a.y;
	err = 2 * ft_abs(dy) - dx;
	while (a.x <= b.x)
	{
		put_pixel_safe(data->img, a.x, y);
		if (err > 0)
		{
			y += (dy > 0) ? 1 : -1;
			err -= 2 * dx;
		}
		err += 2 * ft_abs(dy);
		a.x++;
	}
}

void	draw_line_high(t_data *data, t_point_render a, t_point_render b)
{
	int	dx;
	int	dy;
	int	err;
	int	x;

	dx = b.x - a.x;
	dy = b.y - a.y;
	x = a.x;
	err = 2 * ft_abs(dx) - dy;
	while (a.y <= b.y)
	{
		put_pixel_safe(data->img, x, a.y);
		if (err > 0)
		{
			x += (dx > 0) ? 1 : -1;
			err -= 2 * dy;
		}
		err += 2 * ft_abs(dx);
		a.y++;
	}
}

void	draw_line(t_data *data, t_point_render start, t_point_render end)
{
	if (is_offscreen(start, end))
		return;
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			draw_line_low(data, end, start);
		else
			draw_line_low(data, start, end);
	}
	else
	{
		if (start.y > end.y)
			draw_line_high(data, end, start);
		else
			draw_line_high(data, start, end);
	}
}
void	call_line_drawing(t_data *data, int x, int y)
{
	t_map			*map;
	t_point_render	p0;
	t_point_render	p1;

	map = data->map;
	p0 = map->points_render[y][x];
	if (x + 1 < map->width)
	{
		p1 = map->points_render[y][x + 1];
		draw_line(data, p0, p1);
	}
	if (y + 1 < map->height)
	{
		p1 = map->points_render[y + 1][x];
		draw_line(data, p0, p1);
	}
}
void	render_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			call_line_drawing(data, x, y);
			x++;
		}
		y++;
	}
}


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
	else if ((keydata.key == MLX_KEY_KP_ADD || keydata.key == MLX_KEY_EQUAL) && data->camera.zoom < 50)
		data->camera.zoom *= 1.1;
	else if ((keydata.key == MLX_KEY_KP_SUBTRACT || keydata.key == MLX_KEY_MINUS) && data->camera.zoom > 0.1)
		data->camera.zoom *= 0.9;
	free_points_render(data->map);
	calc_render_points(data->map, &data->camera);
	mlx_delete_image(data->mlx, data->img);
	init_image(&data->img, data->mlx);
	render_map(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (ac != 2)
		return (ft_putstr_fd("Usage ./fdf <location and name>\n", 2), 1);
	if (!init_all(&data, av[1]))
		return (ft_putstr_fd("Initialization failed\n", 2), 1);
	mlx_key_hook(data.mlx, handle_key, &data);
	mlx_close_hook(data.mlx, handle_close, &data);
	mlx_loop(data.mlx);
	cleanup_data(&data);

	return (0);
}
