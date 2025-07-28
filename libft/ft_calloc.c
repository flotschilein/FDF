/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:13:28 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/13 19:12:48 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*ptr_count;
	size_t			i;
	size_t			total_size;

	total_size = count * size;
	ptr = malloc(total_size);
	i = 0;
	if (!ptr)
		return (NULL);
	ptr_count = (unsigned char *)ptr;
	while (i < total_size)
	{
		ptr_count[i] = '\0';
		i++;
	}
	return (ptr);
}

// int main(void)
// {
// 	int	*arr = (int *)ft_calloc(3, sizeof(int));
// 	int	len;

// 	len = 0;

//     while (len < 3)
// 	{
// 		printf("%d", arr[len]);
// 		len++;
// 	}
// 	free(arr);
// 	return 0;
// }
