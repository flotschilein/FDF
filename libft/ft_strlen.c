/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:17:32 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/14 17:40:04 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	const char	*counter;

	counter = (char *)s;
	while (*counter++ != '\0')
		;
	return (counter - s - 1);
}

// int main(void)
// {
// 	const char *test_string = "";

// 	printf("Length of \"%s\" is: %zu\n", test_string, ft_strlen(test_string));
// }
