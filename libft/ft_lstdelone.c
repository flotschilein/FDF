/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:12:36 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/18 16:51:49 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del (lst->content);
	free (lst);
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
// 	t_list *temp = head;

// 	while (temp != NULL)
// 	{
// 		printf("%s\n", (char *)temp->content);
// 		temp = temp->next;
// 	}
// 	node1->next = NULL;
// 	ft_lstdelone(node2, del);
// 	temp = head;
// 	while (temp != NULL)
// 	{
// 		printf("%s\n", (char *)temp->content);
// 		temp = temp->next;
// 	}
// 	while (head != NULL)
// 	{
// 		t_list *next = head->next;
// 		ft_lstdelone(head, del);
// 		head = next;
// 	}
// }
