/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:41 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/20 16:53:32 by fbraune          ###   ########.fr       */
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

int main(int argc, char **argv)
{

	return (0);
}
