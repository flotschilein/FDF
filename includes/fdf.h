/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:21:39 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/06 20:47:27 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
