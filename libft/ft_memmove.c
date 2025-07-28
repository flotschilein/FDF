/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:23:30 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/13 19:32:48 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (dst == src || len == 0)
		return (dst);
	if (d > s)
	{
		d += len - 1;
		s += len - 1;
		while (len-- > 0)
			*d-- = *s--;
	}
	else
	{
		while (len-- > 0)
			*d++ = *s++;
	}
	return (dst);
}

// int main()
// {
// 	char src[] = "Hello, World!";
// 	char dst[20];

// 	ft_memmove(dst, src, sizeof(src));
// 	printf("%s\n", dst);
// }
