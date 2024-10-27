/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daong <daong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:36:20 by daong             #+#    #+#             */
/*   Updated: 2024/05/31 13:55:43 by daong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*x;
	t_list	*new_lst;
	t_list	*new_node;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	x = lst;
	new_lst = (NULL);
	new_node = new_lst;
	while (x != NULL)
	{
		new = f(x->content);
		new_node = ft_lstnew(new);
		if (!new_node)
		{
			del(new);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		x = x->next;
	}
	return (new_lst);
}
