/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:41 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/08 15:45:25 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/fdf.h"
typedef struct s_point
{
    int x;
    int y;
    int z;
    int color;
} t_point;

typedef struct s_map
{
    int         width;
    int         height;
    t_point     **points;
} t_map;

typedef struct s_camerainfo
{
    double      zoom;
    double      angle_x;
    double      angle_y;
    double      angle_z;
    int         offset_x;
    int         offset_y;
} t_camerainfo;

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
		point->color = ft_atoi_base(split[1], "0123456789ABCDEF");
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
	map->points = malloc(sizeof(t_point *) * map->height)
	if (!map->points)
		return (true);
	while ((line = get_next_line(fd)))
	{
		map->points[y] = malloc(sizeof(t_point) * map->width);
		if (!map->points[y])
			return (free(line), true);
		if(!map->points[y] || ft_fill_x(line, map->points[y], map->width, y))
			return (free(line), true);
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

t_map *parse_map(char *filename)
{
	int		fd1;
	int		fd2;
	t_map	*map;
	bool	error;

	error = false;
	fd1 = open(filename, O_RDONLY);
	fd2 = open(filename, O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
		return (ft_putstr_fd("Error: Could not open file\n", 2) ,NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (ft_putstr_fd("Error: Allocation failed\n", 2), NULL);
	map->width = 0;
	map->height = 0;
	map->points = NULL;
	error = ft_map_size(fd, map);
	if (map->width <= 0 || map->height <= 0 || error)
		return (ft_putstr_fd("Error: Invalid map \n", 2), free(map), NULL);
    error = ft_fill_map(fd, map);
	if(error)
		return(fd_putstr_fd("Error: Allocation failed\n", 2), NULL);
	return (close(fd1), close(fd2),map);
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

}