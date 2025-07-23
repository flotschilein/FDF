/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:41 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/23 18:03:29 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (ac != 2)
		return (ft_putstr_fd("Usage ./fdf <location and name>\n", 2), 1);
	if (!init_all(&data, av[1]))
		return (ft_putstr_fd("Initialization failed\n", 2), 1);
	mlx_key_hook(data.mlx, handle_key, &data);
	mlx_close_hook(data.mlx, handle_close, &data);
	mlx_loop(data.mlx);
	cleanup_data(&data);
	return (0);
}
