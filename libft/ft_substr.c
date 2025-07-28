/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:10:28 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/20 19:10:42 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;
	size_t	s_len;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len > start)
	{
		while (s[start + i] != '\0' && i < len)
			i++;
	}
	sub = malloc(i + 1);
	if (!sub)
		return (NULL);
	while (j < i && i != 0)
	{
		sub[j] = s[start + j];
		j++;
	}
	sub[j] = '\0';
	return (sub);
}

// int main(void)
// {
// 	const char *str = "Hello, World!";
// 	char *result = ft_substr(str, 6, 5);
// 	printf("%s\n", result);
// }