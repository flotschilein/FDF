/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:21:39 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/23 16:32:48 by fbraune          ###   ########.fr       */
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


#endif
