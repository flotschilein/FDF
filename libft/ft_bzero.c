/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:09:16 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/13 19:34:11 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n-- >= 1)
		*ptr++ = '\0';
	return (s);
}

// int main(void)
// {
// 	int	len;
// 	len = 0;
// 	char str[] = "hii";
// 	printf("%s \n", str);
// 	ft_bzero(str, 2);
// 	while (len < 3)
// 	{
// 		if (str[len] == 0)
// 			printf("0");
// 		else
// 			printf("%c", str[len]);
// 		len++;
// 	}
// }
