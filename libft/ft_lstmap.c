/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:58:15 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/18 18:58:36 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res_lst;
	t_list	*new_part;
	void	*content;

	res_lst = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst != NULL)
	{
		content = f(lst->content);
		new_part = ft_lstnew(content);
		if (!new_part)
		{
			del(content);
			ft_lstclear(&res_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&res_lst, new_part);
		lst = lst->next;
	}
	return (res_lst);
}

// void *to_uppercase(void *content) {
// 	int i;

// 	i = 0;
// 	char *str = ft_strdup((char *)content);
// 	while (str[i] != '\0')
// 	{
// 		str[i] = ft_toupper(str[i]);
// 		i++;
// 	}
// 	return (str);
// }

// void del(void *content)
// {
// 	free(content);
// }

// int main()
// {
// 	t_list *head = NULL;
// 	t_list *res	 = NULL;

// 	t_list *node1 = ft_lstnew("sgsd3QWdsdd");
// 	t_list *node2 = ft_lstnew("uduifiuydgshHYFsyuaud78387");
// 	ft_lstadd_back(&head, node1);
// 	ft_lstadd_back(&head, node2);
// 	res = ft_lstmap(head, to_uppercase, del);
// 	while (res != NULL)
// 	{
// 		printf("%s\n", (char *)res->content);
// 		res = res->next;
// 	}
// }
