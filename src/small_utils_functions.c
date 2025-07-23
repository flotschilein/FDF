/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_utils_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:53:44 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/23 16:58:38 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

bool	is_offscreen(t_point_render start, t_point_render end)
{
	return ((start.x < 0 && end.x < 0) || (start.x >= 1000 && end.x >= 1000)
		|| (start.y < 0 && end.y < 0) || (start.y >= 1000 && end.y >= 1000));
}

int	ft_abs(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

void	put_pixel_safe(mlx_image_t *img, int x, int y)
{
	if (x >= 0 && x < 1000 && y >= 0 && y < 1000)
		mlx_put_pixel(img, x, y, 0xFFFFFFFF);
}

void	handle_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	cleanup_data(data);
	exit(0);
}
