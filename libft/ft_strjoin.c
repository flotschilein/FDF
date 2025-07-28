/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:27:16 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/14 16:44:35 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	char	*new;

	len = 0;
	i = 0;
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	len = ft_strlen(s1) +ft_strlen(s2);
	i = 0;
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	len = 0;
	while (s1[i] != '\0')
		new[len++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		new[len++] = s2[i++];
	new[len] = '\0';
	return (new);
}

// int main()
// {
// 	char const *str1 = "TEST 123 ,c sdasd  r3ewd";
// 	char const *str2 = "TEST 123 ,c sdasd  r3ewd";

// 	printf("%s", ft_strjoin(str1, str2));
// }
