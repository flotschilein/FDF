/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:41 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/20 20:05:22 by fbraune          ###   ########.fr       */
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
	s_point_in		**points_in;
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
		if (ft_arraylen(split) == 0)
			return (close(fd), ft_putstr_fd("Error calc\n", 2), free(line), ft_free_split(split), false);
		if (*width == 0)
			*width = ft_arraylen(split);
		else if (ft_arraylen(split) != *width)
			return (close(fd), ft_putstr_fd("Error calc\n", 2), free(line), ft_free_split(split), false);
		free(line);
		ft_free_split(split);
		(*height)++;
	}
	return (close(fd), *width > 0 && *height > 0);
}

bool

bool	read_map_points(t_map *map, char *filename)
{
	int fd;
	char *line;
	char **split;
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error read\n", 2), false);
	if (!allocate_map(map, map->width, map->height))
		return (close(fd), ft_putstr_fd("Error read\n", 2), false);

}
bool	init_map(t_map *map, char *filename)
{
	if (!calc_map_size(map->width, map->height, filename))
		return (false);
	if (!read_map_points(map, filename))
		return (false);
}

bool	init_mlx(mlx_t *mlx)
{
	mlx = mlx_init(1000, 1000, "FDF", false);
	if (!mlx)
		return (false);
	return (true);
}

bool	init_all(t_data *data, char *filename)
{
	if(!init_mlx(data->mlx))
		return (false);
	if(!init_map(data->map, filename))
		return (false);
	if(!init_camera(data->camera))
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
