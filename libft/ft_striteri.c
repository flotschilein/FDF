/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:34:43 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/14 16:37:51 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}

// void testmakesmallbigateven(unsigned int i, char *c)
// {
// 	if(i % 2 == 0 && *c >= 'a' && *c <= 'z')
// 		*c = *c - 32;
// }

// int main()
// {
// 	char str[] = "TswT 123 ,c sdasd  r3ewd";
// 	ft_striteri(str, testmakesmallbigateven);
// 	printf("%s", str);
// }
