/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:57:23 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/23 18:00:32 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
			if (dy > 0)
				y += 1;
			else
				y -= 1;
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
			if (dx > 0)
				x += 1;
			else
				x -= 1;
			err -= 2 * dy;
		}
		err += 2 * ft_abs(dx);
		a.y++;
	}
}

void	draw_line(t_data *data, t_point_render start, t_point_render end)
{
	if (is_offscreen(start, end))
		return ;
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
