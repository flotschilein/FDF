/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:41 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/17 21:51:06 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/fdf.h"
#include "MLX42/MLX42.h"
#include <math.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool ft_fill_point(char *data, t_point *point, int x, int y)
{
	char **split;

	split = ft_split(data, ',');
	if (!split)
		return (true);
	if (!split[0])
		return (ft_free_split(split), true);
	point->x = x;
	point->y = y;
	point->z = ft_atoi(split[0]);
	if (!split[1])
		point->color = 0xFFFFFF;
	else
	{
		point->color = ft_atoi_base(split[1] + 2, "0123456789ABCDEF");
		if (point->color < 0)
			point->color = 0xFFFFFF;
	}
	ft_free_split(split);
	return (false);
}

bool ft_fill_x(char *line, t_point *points, int width, int y)
{
	char **split;
	int x;

	x = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (true);
	while (x < width)
	{
		if (!split[x] || ft_fill_point(split[x], &points[x], x, y))
			return (ft_free_split(split), true);
		x++;
	}
	ft_free_split(split);
	return (false);
}

bool ft_fill_map(int fd,t_map *map)
{
	char *line;
	int y;

	y = 0;
	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		return (true);
	while ((line = get_next_line(fd)))
	{
		map->points[y] = malloc(sizeof(t_point) * map->width);
		if (!map->points[y])
			return (free(line), true);
		if(ft_fill_x(line, map->points[y], map->width, y))
		{
			free(line);
			free(map->points[y]);
			while (y > 0)
			    free(map->points[--y]);
			return (free(map->points),true);
		}
		free(line);
		y++;
	}
	return(y != map->height);
}

bool ft_map_size(int fd, t_map *map)
{
	char *line;

	map->width = 0;
	map->height = 0;
	while ((line = get_next_line(fd)))
	{
		if (map->width == 0)
			map->width = ft_count_words(line, ' ');
		map->height++;
		if (map->width != ft_count_words(line, ' '))
			return (free(line), true);
		free(line);
	}
	return (false);
}

bool	validate_map(int fd[2], t_map *map)
{
	bool	error;

	error = ft_map_size(fd[0], map);
	close(fd[0]);
	if (map->width <= 0 || map->height <= 0 || error)
	{
		close(fd[1]);
		ft_putstr_fd("Error: Invalid map\n", 2);
		return (true);
	}
	return (false);
}

bool	init_map_struct(t_map **map)
{
	*map = malloc(sizeof(t_map));
	if (!*map)
	{
		ft_putstr_fd("Error: Allocation failed\n", 2);
		return (true);
	}
	(*map)->width = 0;
	(*map)->height = 0;
	(*map)->points = NULL;
	return (false);
}

bool open_fds(int fd[2], char *filename)
{
	fd[0] = open(filename, O_RDONLY);
	fd[1] = open(filename, O_RDONLY);
	if (fd[0] < 0 || fd[1] < 0)
	{
		if (fd[0] >= 0)
			close(fd[0]);
		if (fd[1] >= 0)
			close(fd[1]);
		ft_putstr_fd("Error: Could not open file\n", 2);
		return (true);
	}
	return (false);
}

void	free_map(t_map *map)
{
	int	y;

	if (!map)
		return ;
	if (map->points)
	{
		y = 0;
		while (y < map->height)
		{
			free(map->points[y]);
			y++;
		}
		free(map->points);
	}
	free(map);
}

t_map *parse_map(char *filename)
{
	int		fd[2];
	t_map	*map;
	bool	error;

	if(!filename || !*filename)
		return (ft_putstr_fd("Error: Invalid filename\n", 2), NULL);
	if (open_fds(fd, filename))
		return (NULL);
	if (init_map_struct(&map))
		return (close(fd[0]), close(fd[1]), NULL);
	if (validate_map(fd, map))
		return (free(map), NULL);
	error = ft_fill_map(fd[1], map);
	close(fd[1]);
	if (error)
		return (free_map(map), ft_putstr_fd("Map parse failed\n", 2), NULL);
	return (map);
}

int	isometric_x(t_point p, t_camerainfo *cam)
{
	return (cos(cam->angle_x) * (p.x - p.y) * cam->zoom + cam->offset_x);
}

int	isometric_y(t_point p, t_camerainfo *cam)
{
	return (sin(cam->angle_y) * (p.x + p.y) * cam->zoom - p.z * cam->zoom + cam->offset_y);
}

void	draw_line(t_data *data, t_point a, t_point b)
{
	int dx = abs(b.x - a.x);
	int dy = abs(b.y - a.y);
	int sx = (a.x < b.x) ? 1 : -1;
	int sy = (a.y < b.y) ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		mlx_pixel_put(data->mlx, data->win, a.x, a.y, a.color);
		if (a.x == b.x && a.y == b.y)
			break;
		e2 = 2 * err;
		if (e2 > -dy) { err -= dy; a.x += sx; }
		if (e2 < dx) { err += dx; a.y += sy; }
	}
}

void draw_horizontal_lines(t_data *data, int y)
{
    int x;
    t_point a, b;

    x = 0;
    while (x < data->map->width)
    {
        a = data->map->points[y][x];
        a.x = isometric_x(a, &data->camera);
        a.y = isometric_y(a, &data->camera);
        if (x + 1 < data->map->width)
        {
            b = data->map->points[y][x + 1];
            b.x = isometric_x(b, &data->camera);
            b.y = isometric_y(b, &data->camera);
            draw_line(data, a, b);
        }
        x++;
    }
}

void draw_vertical_lines(t_data *data, int x)
{
    int y;
    t_point a, b;

    y = 0;
    while (y < data->map->height)
    {
        a = data->map->points[y][x];
        a.x = isometric_x(a, &data->camera);
        a.y = isometric_y(a, &data->camera);
        if (y + 1 < data->map->height)
        {
            b = data->map->points[y + 1][x];
            b.x = isometric_x(b, &data->camera);
            b.y = isometric_y(b, &data->camera);
            draw_line(data, a, b);
        }
        y++;
    }
}

void draw_map(t_data *data)
{
    int y;
    int x;

    y = 0;
	x = 0;
    while (y < data->map->height)
    {
        draw_horizontal_lines(data, y);
        y++;
    }
    while (x < data->map->width)
    {
        draw_vertical_lines(data, x);
        x++;
    }
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	else if (keycode == 65361)
		data->camera.offset_x -= 10;
	else if (keycode == 65363)
		data->camera.offset_x += 10;
	else if (keycode == 65362)
		data->camera.offset_y -= 10;
	else if (keycode == 65364)
		data->camera.offset_y += 10;
	else if (keycode == 61 && data->camera.zoom < 100)
		data->camera.zoom *= 1.1;
	else if (keycode == 45 && data->camera.zoom > 1)
		data->camera.zoom /= 1.1;

	mlx_clear_window(data->mlx, data->win);
	draw_map(data);
	return (0);
}

int close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free_map(data->map);
	exit(0);
}

void	init_camera(t_camerainfo *cam)
{
	cam->zoom = 20;
	cam->angle_x = 0.523599;
	cam->angle_y = 0.523599;
	cam->angle_z = 0;
	cam->offset_x = 500;
	cam->offset_y = 500;
}

void init_mlx(t_map *map)
{
    t_data	data;

	data.map = map;
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		ft_putstr_fd("Could not initialize MLX\n", 2);
		free_map(map);
		exit(1);
	}
	data.win = mlx_new_window(data.mlx, 1000, 1000, "FDF");
	if (!data.win)
	{
		ft_putstr_fd("Could not create window\n", 2);
		free_map(map);
		exit(1);
	}
	init_camera(&data.camera);
	draw_map(&data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
}

int main(int argc, char **argv)
{
	t_map		*map;

	if (argc != 2)
		return (ft_putstr_fd("Usage: ./fdf <filename>\n", 2), 1);
	map = parse_map(argv[1]);
	if (!map)
		return (ft_putstr_fd("Error: Could not parse map\n", 2), 1);
	init_mlx(map);

	return (0);
}
