/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:18:36 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/18 16:52:08 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;

	if (!lst || !del)
		return ;
	cur = *lst;
	while (*lst != NULL)
	{
		cur = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = cur;
	}
}

// void del (void *content)
// {
// 	free (content);
// }

// int main()
// {
// 	t_list *head = NULL;
// 	char *str1 = ft_strdup("1");
// 	char *str2 = ft_strdup("2");
// 	t_list *node1 = ft_lstnew(str1);
// 	t_list *node2 = ft_lstnew(str2);
// 	ft_lstadd_back(&head, node1);
// 	ft_lstadd_back(&head, node2);
// 	ft_lstclear(&head, del);
// 	if (head == NULL)
// 		printf ("list cleared \n");
// 	else
// 		printf("list not cleared \n");
// }
