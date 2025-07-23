/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_size_fill_points.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:02:41 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/23 17:52:50 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

bool	help_calc_map_size(int fd, int *width, int *height)
{
	char	*line;
	char	**split;
	int		curr_width;

	line = get_next_line(fd);
	while (line != NULL)
	{
		split = ft_split(line, ' ');
		if (!split)
			return (ft_putstr_fd("Error calc\n", 2), free(line), false);
		curr_width = ft_arr_len(split);
		if (curr_width == 0)
			return (ft_putstr_fd("Error calc\n", 2), free(line),
				ft_free_split(split), false);
		if (*width == 0)
			*width = curr_width;
		else if (curr_width != *width)
			return (ft_putstr_fd("Error calc\n", 2), free(line),
				ft_free_split(split), false);
		free(line);
		line = get_next_line(fd);
		ft_free_split(split);
		(*height)++;
	}
	return (true);
}

bool	calc_map_size(int *width, int *height, char *filename)
{
	int		fd;

	*width = 0;
	*height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error calc\n", 2), false);
	if (!help_calc_map_size(fd, width, height))
		return (close(fd), false);
	close(fd);
	return (*width > 0 && *height > 0);
}

bool	fill_row(t_map *map, char **split, int y)
{
	int	x;

	x = 0;
	while (split[x] && x < map->width)
	{
		map->points_in[y][x].x = x;
		map->points_in[y][x].y = y;
		map->points_in[y][x].z = ft_atoi(split[x]);
		x++;
	}
	return (true);
}

bool	fill_val(int fd, t_map *map)
{
	int		y;
	char	*line;
	char	**split;

	y = 0;
	while (y < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			return (ft_putstr_fd("Error read\n", 2), false);
		split = ft_split(line, ' ');
		if (!split)
			return (free(line), ft_putstr_fd("Error read\n", 2), false);
		if (!fill_row(map, split, y))
			return (free(line), ft_free_split(split), false);
		free(line);
		ft_free_split(split);
		y++;
	}
	return (true);
}

bool	read_map_points(t_map *map, char *filename)
{
	int	fd;

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
