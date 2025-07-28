/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:49:00 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/18 17:15:47 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cur;

	if (!f)
		return ;
	cur = lst;
	while (cur != NULL)
	{
		f(cur->content);
		cur = cur->next;
	}
}

// void print(void *content)
// {
// 	printf("Content: %s\n", (char *)content);
// }

// int main()
// {
// 	t_list *head = NULL;

// 	t_list *node1 = ft_lstnew("1");
// 	t_list *node2 = ft_lstnew("2");
// 	ft_lstadd_back(&head, node1);
// 	ft_lstadd_back(&head, node2);
// 	t_list *temp = head;
// 	ft_lstiter(head, print);
// }
