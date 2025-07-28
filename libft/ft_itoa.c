/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:53:21 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/24 18:21:44 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long int n, int len)
{
	if (n < 0)
	{
		len++;
		n = -n;
	}
	if (n >= 10)
		return (ft_len(n / 10, len + 1));
	return (len + 1);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*res;
	long int	nb;

	len = ft_len(n, 0);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	nb = n;
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		res[0] = '0';
	while (nb > 0)
	{
		res[--len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (res);
}

// int main()
// {
// 	int c;

// 	c = 2147483647;
// 	printf("Test: %s\n", ft_itoa(c));
// 	printf("Length: %d\n", ft_len(2147483647, 0));
// }
