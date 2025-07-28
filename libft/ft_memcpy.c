/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:16:03 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/15 16:35:45 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (!dst && !src)
		return (NULL);
	while (n-- > 0)
		*d++ = *s++;
	return (dst);
}

// int main()
// {
// 	char src[] = "Hello, World!";
// 	char dst[20];

// 	ft_memcpy(((void *)0), ((void *)0), 3);
// 	printf("%s\n", dst);
// }
