/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:21:39 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/24 14:40:43 by fbraune          ###   ########.fr       */
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
bool	allocate_map_in(t_map *map, int width, int height);
bool	allocate_map_render(t_map *map, int width, int height);

bool	read_map_points(t_map *map, char *filename);
bool	calc_map_size(int *width, int *height, char *filename);

void	free_points_in(t_map *map);
void	free_points_render(t_map *map);
void	cleanup_data(t_data *data);

bool	init_all(t_data *data, char *filename);
bool	init_image(mlx_image_t **img, mlx_t *mlx);

int		main(int ac, char **av);

bool	calc_render_points(t_map *map, t_camerainfo *cam);

void	handle_key(mlx_key_data_t keydata, void *param);


void	render_map(t_data *data);

void	handle_close(void *param);
void	put_pixel_safe(mlx_image_t *img, int x, int y);
int		ft_abs(int value);
bool	is_offscreen(t_point_render start, t_point_render end);

#endif
