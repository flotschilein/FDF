/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:31:28 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/17 16:42:05 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	char	*trimed;

	begin = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (s1[begin] != '\0' && ft_strchr(set, s1[begin]))
		begin++;
	end = ft_strlen(s1);
	while (end > begin && ft_strchr(set, s1[end - 1]))
		end--;
	trimed = malloc(end - begin + 1);
	if (!trimed)
		return (NULL);
	ft_strlcpy(trimed, s1 + begin, end - begin + 1);
	return (trimed);
}

// int main(void)
// {
// 	char *s1 = "... Hel.lon. . Wor.ld ...";
// 	char *set = "";
// 	char *result = ft_strtrim(s1, set);
// 	printf("%s\n\n", result);
// }
