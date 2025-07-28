/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:51:10 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/13 19:38:09 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len-- >= 1)
		*ptr++ = c;
	return (b);
}

// int main(void)
// {
// 	int	len;
// 	len = 0;
// 	char str[] = "hii";
// 	printf("%s \n", str);
// 	ft_memset(str, 'a', 2);
// 	while (len < 3)
// 	{
// 		if (str[len] == 0)
// 			printf("0");
// 		else
// 			printf("%c", str[len]);
// 		len++;
// 	}
// }
