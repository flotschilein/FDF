/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:23:32 by fbraune           #+#    #+#             */
/*   Updated: 2025/07/07 17:25:01 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi_base(char *nbr, char *base_from)
{
	int			base_length;
	int			i;
	int			j;
	long int	res;

	base_length = ft_length(base_from);
	res = 0;
	i = 0;
	while (nbr[i] != '\0')
	{
		j = 0;
		while (j < base_length && base_from[j] != nbr[i])
			j++;
		if (j == base_length)
			return (res);
		res = res * base_length + j;
		if (res > 2147483647 || res < -2147483648)
			return (0);
		i++;
	}
	return (res);
}
