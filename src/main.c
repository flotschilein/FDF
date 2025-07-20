/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:41 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/20 23:00:07 by fbraune          ###   ########.fr       */
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


typedef struct s_point_in
{
	int		x;
	int		y;
	int		z;
}	t_point_in;

typedef struct s_point_render
{
	int		x;
	int		y;
}	t_point_render;

typedef struct s_map
{
	int				width;
	int				height;
	t_point_in		**points_in;
	t_point_render	**points_render;
}	t_map;

typedef struct s_camerainfo
{
	double		zoom;
	int			offset_x;
	int			offset_y;
}	t_camerainfo;

typedef struct s_data
{
	mlx_t           *mlx;
	t_map           *map;
	t_camerainfo    camera;
	mlx_image_t     *img;
}   t_data;

bool	calc_map_size(int *width, int *height, char *filename)
{
	int fd;
	char *line;
	char **split;

	*width = 0;
	*height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error calc\n", 2), false);
	while ((line = get_next_line(fd)) != NULL)
	{
		split = ft_split(line, ' ');
		if (!split)
			return (close(fd), ft_putstr_fd("Error calc\n", 2), free(line), false);
		if (ft_arr_len(split) == 0)
			return (close(fd), ft_putstr_fd("Error calc\n", 2), free(line), ft_free_split(split), false);
		if (*width == 0)
			*width = ft_arr_len(split);
		else if (ft_arr_len(split) != *width)
			return (close(fd), ft_putstr_fd("Error calc\n", 2), free(line), ft_free_split(split), false);
		free(line);
		ft_free_split(split);
		(*height)++;
	}
	return (close(fd), *width > 0 && *height > 0);
}

void	free_points_in(t_map *map)
{
	int y;

	if (!map->points_in)
		return;
	y = 0;
	while (y < map->height)
	{
		free(map->points_in[y]);
		y++;
	}
	free(map->points_in);
	map->points_in = NULL;
}

bool	allocate_map_render(t_map *map, int width, int height)
{
	int y;

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
	int y;

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
bool	fill_val(int fd, t_map *map)
{
	int		y;
	int		x;
	char	*line;
	char	**split;

	y = 0;
	while ((line = get_next_line(fd)) != NULL && y < map->height)
	{
		split = ft_split(line, ' ');
		if (!split)
			return (free(line), ft_putstr_fd("Error read\n", 2), false);
		x = 0;
		while (split[x] && x < map->width)
		{
			map->points_in[y][x].x = x;
			map->points_in[y][x].y = y;
			map->points_in[y][x].z = ft_atoi(split[x]);
			x++;
		}
		free(line);
		ft_free_split(split);
		y++;
	}
	return (y == map->height);
}

bool	read_map_points(t_map *map, char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error read\n", 2), false);
	if (!allocate_map_in(map, map->width, map->height))
		return (close(fd), ft_putstr_fd("Error read\n", 2), false);
	if (!fill_val(fd, map))
	{
		free_points_in(map);
		return (close(fd), ft_putstr_fd("Error read\n", 2), false);
	}
	close(fd);
	return (true);
}

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

	map->points_render[y][x].x = (int)scaled_x;
	map->points_render[y][x].y = (int)scaled_y;
}

// void print_render_points(t_map *map)
// {
//     printf("\n--- Rendered Points (2D Isometric Projection) ---\n");
//     for (int y = 0; y < map->height; y++)
//     {
//         for (int x = 0; x < map->width; x++)
//         {
//             printf("(%4d, %4d) ", map->points_render[y][x].x, map->points_render[y][x].y);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }

bool	calc_render_points(t_map *map, t_camerainfo *cam)
{
	int y;
	int x;

	if (!allocate_map_render(map, map->width, map->height))
	{
		free_points_in(map);
		return (false);
	}
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

bool	init_map(t_map *map, char *filename,t_camerainfo *cam)
{
	if (!calc_map_size(&map->width, &map->height, filename))
		return (false);
	if (!read_map_points(map, filename))
		return (false);
	if (!calc_render_points(map, cam))
	{
		free_points_in(map);
		return (false);
	}
	return (true);
}

bool	init_mlx(mlx_t *mlx)
{
	mlx = mlx_init(1000, 1000, "FDF", false);
	if (!mlx)
		return (false);
	return (true);
}

void	init_camera(t_camerainfo *camera)
{
	camera->zoom = 100;
	camera->offset_x = 0;
	camera->offset_y = 0;
}

bool	init_all(t_data *data, char *filename)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (ft_putstr_fd("Memory allocation failed\n", 2), false);
	init_camera(&data->camera);
	if(!init_mlx(data->mlx))
		return (false);
	if(!init_map(data->map, filename, &data->camera))
		return (false);
	if(!init_image(data->img, data->mlx))
		return (false);
	return (true);
}


int main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (ft_putstr_fd("Usage ./fdf <location and name>\n", 2), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Memory allocation failed\n", 2), 1);
	if(!init_all(data, av[1]))
		return (ft_putstr_fd("Initialization failed\n", 2), free(data), 1);
	return (0);
}
