/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:21:39 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/23 17:54:57 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_point_in
{
	int				x;
	int				y;
	int				z;
}					t_point_in;

typedef struct s_point_render
{
	int				x;
	int				y;
}					t_point_render;

typedef struct s_map
{
	int				width;
	int				height;
	t_point_in		**points_in;
	t_point_render	**points_render;
}					t_map;

typedef struct s_camerainfo
{
	double			zoom;
	int				offset_x;
	int				offset_y;
}					t_camerainfo;

typedef struct s_data
{
	mlx_t			*mlx;
	t_map			*map;
	t_camerainfo	camera;
	mlx_image_t		*img;
}					t_data;

void	free_points_in(t_map *map);
void	free_points_render(t_map *map);
void	cleanup_data(t_data *data);

bool	allocate_map_in(t_map *map, int width, int height);
bool	allocate_map_render(t_map *map, int width, int height);

bool	init_all(t_data *data, char *filename);
bool	init_image(mlx_image_t **img, mlx_t *mlx);
void	init_camera(t_camerainfo *camera);
bool	init_mlx(t_data *data);
bool	init_map(t_map *map, char *filename, t_camerainfo *cam);

void	handle_close(void *param);
void	put_pixel_safe(mlx_image_t *img, int x, int y);
int		ft_abs(int value);
bool	is_offscreen(t_point_render start, t_point_render end);

bool	read_map_points(t_map *map, char *filename);
bool	fill_val(int fd, t_map *map);
bool	calc_map_size(int *width, int *height, char *filename);

bool	read_map_points(t_map *map, char *filename);
bool	fill_val(int fd, t_map *map);
bool	fill_row(t_map *map, char **split, int y);
bool	calc_map_size(int *width, int *height, char *filename);
bool	help_calc_map_size(int fd, int *width, int *height);

#endif
